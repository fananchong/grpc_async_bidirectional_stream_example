#pragma once

#include "log.hpp"
#include "util.hpp"
#include "tag.hpp"
#include <grpcpp/grpcpp.h>
#include "server.hpp"
#include "context.hpp"
#include <functional>
#include <cassert>
#include <atomic>

class ServerImpl;

extern std::atomic<int64_t> gid;

class IMsg
{
public:
    IMsg() : id_(gid++), context_(nullptr) {}
    IMsg(HandleRpcsContext *context) : id_(gid++), context_(context) {}
    virtual ~IMsg() {}
    int64_t ID() { return id_; }

    virtual void NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) {}
    virtual void Proceed() {}
    virtual void Release() {}
    virtual void OnTrigger() {}

protected:
    int64_t id_;
    HandleRpcsContext *context_;
};

template <class T>
class NotifyMsg : public IMsg
{
public:
    NotifyMsg(HandleRpcsContext *context, T *obj) : IMsg(context), obj_(obj)
    {
    }
    void Proceed() override
    {
        context_->streams_.erase(obj_);
        context_->tags_->Release(obj_);
        delete this;
    }

private:
    T *obj_;
};

// StreamBase 双向流消息基类
template <class T, class Service, class Replay, class Request>
class StreamBase : public IMsg
{
public:
    StreamBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq);
    virtual ~StreamBase();
    void NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) override;
    void Proceed() override;
    void Release() override;
    bool IsClosed() { return closed_; }
    void SendMsg(const Replay &msg, bool isLastMsg = true);         // isLastMsg 值为 false , 表示表示还有 N 条消息待发送
    void SendMsgWithCopy(const Replay &msg, bool isLastMsg = true); // isLastMsg 值为 false , 表示表示还有 N 条消息待发送

    // 子类实现
    virtual void OnCreate() = 0;
    virtual bool OnProcess() = 0;
    virtual void OnExit() = 0;

    // 关闭流
    void CloseStream() { closed_ = true; }

protected:
    Service *service_;
    grpc::ServerCompletionQueue *cq_;
    grpc::ServerContext ctx_;
    Replay reply_;
    Request request_;
    grpc::ServerAsyncReaderWriter<Replay, Request> stream_;

public:
    enum CallStatus
    {
        CREATE,
        INIT_READ,
        READ,
        PROCESS,
        WRITE,
        FINISH,
        CLOSED,
    };
    void SetStatus(CallStatus s);
    int oping_ = 0;

protected:
    CallStatus status_;
    struct WriteInfo
    {
        Replay Rep;
        bool IsLastMsg;
    };
    std::list<WriteInfo> write_list_;
    void OpRead();
    void OpWrite(const Replay &rep, bool isLastMsg);
    void OpWrite();
    bool closed_;
};

// UnitaryBase 一元消息基类
template <class T, class Service, class Replay, class Request>
class UnitaryBase : public IMsg
{
public:
    UnitaryBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq);
    virtual ~UnitaryBase();
    void NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) override;
    void Proceed() override;

    // 子类实现
    virtual void OnCreate() = 0;
    virtual grpc::Status OnProcess() = 0;

protected:
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

#define STREAM_MESSAGE(MSG, SERVICE, ACK, REQ, ...)                                        \
    class MSG                                                                              \
        : public StreamBase<MSG, SERVICE, ACK, REQ>                                        \
    {                                                                                      \
    public:                                                                                \
        MSG(SERVICE *service)                                                              \
            : StreamBase<MSG, SERVICE, ACK, REQ>(service, nullptr, nullptr) {}             \
        MSG(SERVICE *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) \
            : StreamBase<MSG, SERVICE, ACK, REQ>(service, context, cq)                     \
        {                                                                                  \
            PRINT_CONSTRUCTOR(MSG);                                                        \
            assert(context != nullptr);                                                    \
            ctx_.AsyncNotifyWhenDone(new NotifyMsg<MSG>(context, this));                   \
            Proceed();                                                                     \
        }                                                                                  \
        virtual ~MSG()                                                                     \
        {                                                                                  \
            PRINT_DESTRUCTOR(MSG);                                                         \
        }                                                                                  \
        virtual void OnCreate() override;                                                  \
        virtual bool OnProcess() override;                                                 \
        virtual void OnTrigger() override;                                                 \
        virtual void OnExit() override;                                                    \
        __VA_ARGS__;                                                                       \
    }

#define UNITARY_MESSAGE(MSG, SERVICE, ACK, REQ)                                            \
    class MSG                                                                              \
        : public UnitaryBase<MSG, SERVICE, ACK, REQ>                                       \
    {                                                                                      \
    public:                                                                                \
        MSG(SERVICE *service)                                                              \
            : UnitaryBase<MSG, SERVICE, ACK, REQ>(service, nullptr, nullptr) {}            \
        MSG(SERVICE *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) \
            : UnitaryBase<MSG, SERVICE, ACK, REQ>(service, context, cq)                    \
        {                                                                                  \
            PRINT_CONSTRUCTOR(MSG);                                                        \
            assert(context != nullptr);                                                    \
            Proceed();                                                                     \
        }                                                                                  \
        virtual ~MSG()                                                                     \
        {                                                                                  \
            PRINT_DESTRUCTOR(MSG);                                                         \
        }                                                                                  \
        virtual void OnCreate() override;                                                  \
        virtual grpc::Status OnProcess() override;                                         \
    }

#include "msg.ipp"
