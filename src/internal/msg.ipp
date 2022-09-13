#include "log.hpp"

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::StreamBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
    : IMsg(context), service_(service), cq_(cq), stream_(&ctx_), status_(CREATE), closed_(false)
{
    read_swap_.reset(new ReadMsg<T>((T *)this));
    write_swap_.reset(new WriteMsg<T>((T *)this));
}

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::~StreamBase()
{
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
{
    auto v = std::make_shared<T>(service_, context, cq);
    v->ctx_.AsyncNotifyWhenDone(new NotifyMsg<T>(context, v->shared_from_this()));
    v->Proceed();
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::Proceed()
{
    switch (status_)
    {
    case CREATE:
        status_ = INIT_READ;
        OnCreate();
        break;
    case INIT_READ:
        NewMsg(context_, cq_);
    case READ:
        OpProcess();
        OpWriteLock();
        OpRead();
        break;
    case WRITE:
        OpWrite();
        OpRead();
        break;
    case FINISH:
        OnExit();
        ctx_.TryCancel();
        status_ = CLOSED;
        closed_ = true;
        break;
    case CLOSED:
        break;
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::SendMsg(const std::shared_ptr<Replay> &msg)
{
    std::lock_guard<std::mutex> lck(m_mutex_);
    if (oping_w_ == 0)
    {
        if (write_list_.size() == 0)
        {
            OpWrite(msg);
        }
        else
        {
            write_list_.push_back(msg);
            OpWrite();
        }
    }
    else
    {
        write_list_.push_back(msg);
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpProcess()
{
    if (request_ != nullptr && oping_r_ == 0)
    {
        reply_.reset();
        OnProcess();
        if (reply_ != nullptr)
        {
            SendMsg(reply_);
            reply_.reset();
        }
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpRead()
{
    if (oping_r_ == 0)
    {
        oping_r_ = 1;
        request_ = std::make_shared<Request>();
        stream_.Read(request_.get(), read_swap_.get());
        INFO("[stream {}] OpRead", ID());
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite()
{
    if (oping_w_ == 0 && !write_list_.empty())
    {
        oping_w_ = 1;
        stream_.Write(*write_list_.front().get(), write_swap_.get());
        write_list_.pop_front();
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite(const std::shared_ptr<Replay> &msg)
{
    oping_w_ = 1;
    stream_.Write(*msg.get(), write_swap_.get());
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWriteLock()
{
    std::lock_guard<std::mutex> lck(m_mutex_);
    OpWrite();
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWriteLock(const std::shared_ptr<Replay> &msg)
{
    std::lock_guard<std::mutex> lck(m_mutex_);
    OpWrite(msg);
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::SetStatus(CallStatus s)
{
    if (!closed_)
    {
        status_ = s;
    }
    else
    {
        INFO("closed_=true, id={}", id_);
        status_ = FINISH;
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::Release()
{
    OnExit();
    stream_.Finish(grpc::Status::CANCELLED, (T *)this);
    status_ = CLOSED;
    closed_ = true;
}

template <class T, class Service, class Replay, class Request>
UnitaryBase<T, Service, Replay, Request>::UnitaryBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
    : IMsg(context), service_(service), cq_(cq), responder_(&ctx_), status_(CREATE)
{
}

template <class T, class Service, class Replay, class Request>
UnitaryBase<T, Service, Replay, Request>::~UnitaryBase()
{
}

template <class T, class Service, class Replay, class Request>
void UnitaryBase<T, Service, Replay, Request>::NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
{
    new T(service_, context, cq);
}

template <class T, class Service, class Replay, class Request>
void UnitaryBase<T, Service, Replay, Request>::Proceed()
{
    grpc::Status ret;
    switch (status_)
    {
    case CREATE:
        status_ = PROCESS;
        OnCreate();
        break;
    case PROCESS:
        NewMsg(context_, cq_);
        ret = OnProcess();
        status_ = FINISH;
        responder_.Finish(reply_, ret, (T *)this);
        break;
    default:
        GPR_ASSERT(status_ == FINISH);
        delete (T *)this;
        break;
    }
}
