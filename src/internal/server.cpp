#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include <spdlog/fmt/fmt.h>
#include "log.hpp"
#include "server.hpp"
#include "util.hpp"

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

void ServerImpl::Run(const std::string &ip, const std::string &port)
{
    std::string server_address(fmt::format("{}:{}", ip, port));
    builder_->AddListeningPort(server_address, grpc::InsecureServerCredentials());
    cq_ = builder_->AddCompletionQueue();
    server_ = builder_->BuildAndStart();
    if (server_ == nullptr)
    {
        ERR("bind and listen port fail on {}", server_address);
        exit(1);
    }
    INFO("Server listening on {}", server_address);
    ServerImpl::HandleRpcs();
}

void ServerImpl::Stop()
{
    server_->Shutdown();
    cq_->Shutdown();
}

void ServerImpl::HandleRpcs()
{
    for (auto msg : msgs_)
    {
        msg->Accpet(this, cq_.get());
    }
    void *tag;
    bool ok, next;
    do
    {
        next = cq_->Next(&tag, &ok);
        if (next && ok)
        {
            if (auto v = gtags.Get(int64_t(tag)))
            {
                v->Proceed();
            }
        }
    } while (next);
    INFO("HandleRpcs exit.");
}
