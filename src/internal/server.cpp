#include "log.hpp"
#include "server.hpp"
#include "context.hpp"
#include "msg.hpp"
#include "util.hpp"
#include <grpcpp/grpcpp.h>
#include <spdlog/fmt/fmt.h>
#include <thread>
#include <map>

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
    auto max_message_size = 128 * 1024 * 1024;
    auto keepalivetime = 30 * 1000;
    auto keepalivetimeout = 60 * 1000;
    INFO("gRPC Max Message Size: {}M", max_message_size / 1024.0f / 1024.0f);
    INFO("gRPC Keepalive Time: {}s", keepalivetime / 1000.0f);
    INFO("gRPC Keepalive Timeout: {}s", keepalivetimeout / 1000.0f);
    builder_->SetMaxMessageSize(max_message_size);
    builder_->AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, keepalivetime);
    builder_->AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, keepalivetimeout);
    builder_->AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
    builder_->AddChannelArgument(GRPC_ARG_HTTP2_MAX_PING_STRIKES, 0);
    builder_->AddChannelArgument(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);
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
    INFO("Server thread num {}", thread_num);
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
    HandleRpcsContext context;
    for (auto msg : msgs_)
    {
        msg->NewMsg(&context, cq);
    }
    auto pre_fragment = context.current_fragment_; // 上次时间片段
    void *tag;
    bool ok;
    grpc::CompletionQueue::NextStatus next(grpc::CompletionQueue::GOT_EVENT);
    while (next != grpc::CompletionQueue::SHUTDOWN)
    {
        do
        {
            tag = nullptr;
            next = cq->AsyncNext(&tag, &ok, std::chrono::system_clock::now() + std::chrono::milliseconds(10));
            auto fn = [next, ok, &tag]() -> int
            {
                if (next == grpc::CompletionQueue::GOT_EVENT)
                {
                    ((IMsg *)tag)->Proceed();
                    return 1;
                }
                return 0;
            };
            context.Update(fn);
        } while (next == grpc::CompletionQueue::GOT_EVENT && pre_fragment == context.current_fragment_);

        context.tags_->DelayDel(context.current_timestamp_);

        // 时间片段推进，调用触发器
        if (pre_fragment < context.current_fragment_)
        {
            pre_fragment = context.current_fragment_;
            auto fn = [&context, this]()
            {
                context.OnTrigger();
                return 0;
            };
            context.Update(fn);
        }
    }
    INFO("HandleRpcs exit. thread_no={}", thread_no);
}
