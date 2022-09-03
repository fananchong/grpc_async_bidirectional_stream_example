#include "log.hpp"

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::StreamBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
    : IMsg(context), service_(service), cq_(cq), stream_(&ctx_), status_(CREATE), closed_(false)
{
    read_swap.reset(new ReadMsg<T>((T *)this));
    write_swap.reset(new WriteMsg<T>((T *)this));
}

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::~StreamBase()
{
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::NewMsg(HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
{
    new T(service_, context, cq);
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
        context_->streams_.insert((T *)this);
    case READ:
        reply_.Clear();
        if (OnProcess())
        {
            SendMsg(reply_);
        }
        OpRead();
        break;
    case WRITE:
        OpWrite();
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
void StreamBase<T, Service, Replay, Request>::SendMsg(const Replay &msg)
{
    if (oping_ == 0)
    {
        if (write_list_.size() == 0)
        {
            OpWrite(msg);
        }
        else
        {
            auto v = std::make_shared<Replay>();
            v->CopyFrom(msg);
            write_list_.push_back(v);
            OpWrite();
        }
    }
    else
    {
        auto v = std::make_shared<Replay>();
        v->CopyFrom(msg);
        write_list_.push_back(v);
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpRead()
{
    request_.Clear();
    stream_.Read(&request_, read_swap.get());
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite()
{
    if (oping_ == 0 && !write_list_.empty())
    {
        oping_ = 1;
        auto &rep = write_list_.front();
        stream_.Write(*rep, write_swap.get());
        write_list_.pop_front();
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite(const Replay &rep)
{
    oping_ = 1;
    stream_.Write(rep, write_swap.get());
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
