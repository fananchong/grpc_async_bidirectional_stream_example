#pragma once

#include "log.hpp"
#include "util.hpp"
#include "tag.hpp"
#include <grpcpp/grpcpp.h>
#include <functional>
#include <cassert>
#include <atomic>

class ServerImpl;

extern std::atomic<int64_t> gid;

class IMsg
{
public:
    IMsg() : id_(gid++) {}
    virtual ~IMsg() {}
    int64_t ID() { return id_; };

    virtual void Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags) = 0;
    virtual void Proceed() = 0;
    virtual void Release() {}

protected:
    int64_t id_;
};

template <class T>
class NotifyMsg : public IMsg
{
public:
    NotifyMsg(T *obj, Tag *tags) : obj_(obj), tags_(tags) {}
    void Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags) override {}
    void Proceed() override
    {
        tags_->Release(obj_);
        delete this;
    }

private:
    T *obj_;
    Tag *tags_;
};

// StreamBase 双向流消息基类
template <class T, class Service, class Replay, class Request>
class StreamBase : public IMsg
{
public:
    StreamBase(Service *service, ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags);
    virtual ~StreamBase();
    void Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags) override;
    void Proceed() override;
    void Release() override;
    // bool IsCancelled() { return ctx_.IsCancelled(); }
    bool IsClosed() { return closed_; }

    // 子类实现
    virtual void OnCreate() = 0;
    virtual void OnProcess() = 0;
    virtual void OnExit() = 0;

    // 关闭流
    void CloseStream() { closed_ = true; }

protected:
    ServerImpl *server_;
    Service *service_;
    grpc::ServerCompletionQueue *cq_;
    grpc::ServerContext ctx_;
    Replay reply_;
    Request request_;
    grpc::ServerAsyncReaderWriter<Replay, Request> stream_;
    enum CallStatus
    {
        CREATE,
        INIT_READ,
        READ,
        WRITE,
        FINISH,
        CLOSED,
    };
    CallStatus status_;
    Tag *tags_;
    bool closed_;
};

// UnitaryBase 一元消息基类
template <class T, class Service, class Replay, class Request>
class UnitaryBase : public IMsg
{
public:
    UnitaryBase(Service *service, ServerImpl *server, grpc::ServerCompletionQueue *cq);
    virtual ~UnitaryBase();
    void Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags) override;
    void Proceed() override;

    // 子类实现
    virtual void OnCreate() = 0;
    virtual grpc::Status OnProcess() = 0;

protected:
    ServerImpl *server_;
    Service *service_;
    grpc::ServerCompletionQueue *cq_;
    grpc::ServerContext ctx_;
    Replay reply_;
    Request request_;
    grpc::ServerAsyncResponseWriter<Replay> responder_;
    enum CallStatus
    {
        CREATE,
        PROCESS,
        FINISH,
    };
    CallStatus status_;
};

#define STREAM_MESSAGE(MSG, SERVICE, ACK, REQ, ...)                                           \
    class MSG                                                                                 \
        : public StreamBase<MSG, SERVICE, ACK, REQ>                                           \
    {                                                                                         \
    public:                                                                                   \
        MSG(SERVICE *service)                                                                 \
            : StreamBase<MSG, SERVICE, ACK, REQ>(service, nullptr, nullptr, nullptr) {}       \
        MSG(SERVICE *service, ServerImpl *server, grpc::ServerCompletionQueue *cq, Tag *tags) \
            : StreamBase<MSG, SERVICE, ACK, REQ>(service, server, cq, tags)                   \
        {                                                                                     \
            PRINT_CONSTRUCTOR(MSG);                                                           \
            if (server != nullptr)                                                            \
            {                                                                                 \
                ctx_.AsyncNotifyWhenDone(new NotifyMsg<MSG>(this, this->tags_));              \
                Proceed();                                                                    \
            }                                                                                 \
        }                                                                                     \
        virtual ~MSG()                                                                        \
        {                                                                                     \
            PRINT_DESTRUCTOR(MSG);                                                            \
        }                                                                                     \
        virtual void OnCreate() override;                                                     \
        virtual void OnProcess() override;                                                    \
        virtual void OnExit() override;                                                       \
        __VA_ARGS__;                                                                          \
    }

#define UNITARY_MESSAGE(MSG, SERVICE, ACK, REQ)                                    \
    class MSG                                                                      \
        : public UnitaryBase<MSG, SERVICE, ACK, REQ>                               \
    {                                                                              \
    public:                                                                        \
        MSG(SERVICE *service)                                                      \
            : UnitaryBase<MSG, SERVICE, ACK, REQ>(service, nullptr, nullptr) {}    \
        MSG(SERVICE *service, ServerImpl *server, grpc::ServerCompletionQueue *cq) \
            : UnitaryBase<MSG, SERVICE, ACK, REQ>(service, server, cq)             \
        {                                                                          \
            PRINT_CONSTRUCTOR(MSG);                                                \
            if (server != nullptr)                                                 \
            {                                                                      \
                Proceed();                                                         \
            }                                                                      \
        }                                                                          \
        virtual ~MSG()                                                             \
        {                                                                          \
            PRINT_DESTRUCTOR(MSG);                                                 \
        }                                                                          \
        virtual void OnCreate() override;                                          \
        virtual grpc::Status OnProcess() override;                                 \
    }

#include "msg.ipp"
