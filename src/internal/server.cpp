#include "log.hpp"
#include "server.hpp"
#include "util.hpp"
#include <grpcpp/grpcpp.h>
#include <spdlog/fmt/fmt.h>
#include <thread>

using grpc::Server;
using grpc::ServerAsyncReaderWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

ServerImpl::ServerImpl()
    : builder_(new ServerBuilder())
{
}

ServerImpl::~ServerImpl()
{
}

void ServerImpl::RegisterService(grpc::Service *service)
{
    builder_->RegisterService(service);
}

void ServerImpl::RegisterMsg(IMsg *msg)
{
    msgs_.push_back(msg);
}

void ServerImpl::Run(size_t thread_num, const std::string &ip, const std::string &port)
{
    std::string server_address(fmt::format("{}:{}", ip, port));
    builder_->AddListeningPort(server_address, grpc::InsecureServerCredentials());
    for (size_t i = 0; i < thread_num; i++)
    {
        cq_.push_back(builder_->AddCompletionQueue());
    }
    server_ = builder_->BuildAndStart();
    if (server_ == nullptr)
    {
        ERR("bind and listen port fail on {}", server_address);
        exit(1);
    }
    INFO("Server listening on {}", server_address);
    std::vector<std::thread> threads;
    for (size_t i = 1; i < thread_num; i++)
    {
        threads.push_back(std::thread(&ServerImpl::HandleRpcs, this, i));
    }
    ServerImpl::HandleRpcs(0);
    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
}

void ServerImpl::Stop()
{
    server_->Shutdown();
    for (size_t i = 0; i < cq_.size(); i++)
    {
        cq_[i]->Shutdown();
    }
}

void ServerImpl::HandleRpcs(size_t thread_no)
{
    auto cq = cq_[thread_no].get();
    Tag tags;
    for (auto msg : msgs_)
    {
        msg->Accpet(this, cq, &tags);
    }
    void *tag;
    bool ok;
    grpc::CompletionQueue::NextStatus next(grpc::CompletionQueue::GOT_EVENT);
    while (next != grpc::CompletionQueue::SHUTDOWN)
    {
        do
        {
            auto deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(50);
            next = cq->AsyncNext(&tag, &ok, deadline);
            if (next == grpc::CompletionQueue::GOT_EVENT && ok)
            {
                ((IMsg *)tag)->Proceed();
            }
        } while (next == grpc::CompletionQueue::GOT_EVENT);
        tags.DelayDel();
    }
    INFO("HandleRpcs exit.");
}
