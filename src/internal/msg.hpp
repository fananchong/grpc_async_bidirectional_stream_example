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
#include <memory>
#include <mutex>

class ServerImpl;

int64_t gen_id();

class IMsg
{
public:
    IMsg() : id_(gen_id()), context_(nullptr) {}
    IMsg(HandleRpcsContext *context) : id_(gen_id()), context_(context) {}
    virtual ~IMsg() {}
    int64_t ID() { return id_; }

    virtual void NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) {}
    virtual void Proceed() {}
    virtual void Release() {}

protected:
    int64_t id_;
    HandleRpcsContext *context_;
};

template <class T>
class NotifyMsg : public IMsg
{
public:
    NotifyMsg(HandleRpcsContext *context, const std::shared_ptr<T> &obj) : IMsg(context), obj_(obj)
    {
    }
    void Proceed() override
    {
        context_->tags_->Release(obj_);
        delete this;
    }

private:
    std::shared_ptr<T> obj_;
};

template <class T>
class ReadMsg : public IMsg
{
public:
    ReadMsg(T *obj) : obj_(obj) {}
    void Proceed() override
    {
        obj_->oping_r_ = 0;
        obj_->SetStatus(T::READ);
        obj_->Proceed();
    }

private:
    T *obj_;
};

template <class T>
class WriteMsg : public IMsg
{
public:
    WriteMsg(T *obj) : obj_(obj) {}
    void Proceed() override
    {
        std::lock_guard<std::mutex> lck(obj_->m_mutex_);
        obj_->oping_w_ = 0;
        obj_->SetStatus(T::WRITE);
        obj_->Proceed();
    }

private:
    T *obj_;
};

// StreamBase 双向流消息基类
template <class T, class Service, class Replay, class Request>
class StreamBase : public IMsg, public std::enable_shared_from_this<T>
{
public:
    StreamBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq);
    virtual ~StreamBase();
    void NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq) override;
    void Proceed() override;
    void Release() override;
    bool IsClosed() { return closed_; }
    void SendMsg(const std::shared_ptr<Replay> &msg);

    // 子类实现
    virtual void OnCreate() = 0;
    virtual void OnProcess() = 0;
    virtual void OnExit() = 0;

    // 关闭流
    void CloseStream() { closed_ = true; }

protected:
    Service *service_;
    grpc::ServerCompletionQueue *cq_;
    grpc::ServerContext ctx_;
    std::shared_ptr<Replay> reply_;
    std::shared_ptr<Request> request_;
    grpc::ServerAsyncReaderWriter<Replay, Request> stream_;

public:
    enum CallStatus
    {
        CREATE,
        INIT_READ,
        READ,
        WRITE,
        FINISH,
        CLOSED,
    };
    void SetStatus(CallStatus s);
    int oping_r_ = 0;
    int oping_w_ = 0;
    std::mutex m_mutex_;

protected:
    CallStatus status_;
    std::list<std::shared_ptr<Replay>> write_list_;
    void OpRead();
    void OpWrite();
    void OpWrite(const std::shared_ptr<Replay> &rep);
    void OpWriteLock();
    void OpWriteLock(const std::shared_ptr<Replay> &rep);
    void OpProcess();
    std::unique_ptr<ReadMsg<T>> read_swap_;
    std::unique_ptr<WriteMsg<T>> write_swap_;
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
        }                                                                                  \
        virtual ~MSG()                                                                     \
        {                                                                                  \
            PRINT_DESTRUCTOR(MSG);                                                         \
        }                                                                                  \
        virtual void OnCreate() override;                                                  \
        virtual void OnProcess() override;                                                 \
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
