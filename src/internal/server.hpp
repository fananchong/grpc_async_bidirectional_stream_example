#pragma once

#include <memory>
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "msg.hpp"

class ServerImpl final
{
public:
    ServerImpl();
    ~ServerImpl();

    void RegisterService(grpc::Service *service);
    void RegisterMsg(IMsg *msg);
    void Run(const std::string &ip, const std::string &port);
    void Stop();

private:
    void HandleRpcs();

    std::unique_ptr<grpc::ServerBuilder> builder_;
    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;
    std::vector<IMsg *> msgs_;
};
