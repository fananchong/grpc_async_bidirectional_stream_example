#include "log.hpp"

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::StreamBase(Service *service, HandleRpcsContext *context, grpc::ServerCompletionQueue *cq)
    : IMsg(context), service_(service), cq_(cq), stream_(&ctx_), status_(CREATE), closed_(false)
{
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
    oping_ = 0;
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
        OpRead();
        break;
    case PROCESS:
        reply_.Clear();
        if (OnProcess())
        {
            SendMsgWithCopy(reply_);
        }
        break;
    case WRITE:
        OpWrite();
        break;
    case FINISH:
        OnExit();
        ctx_.TryCancel();
        status_ = CLOSED;
        break;
    case CLOSED:
        break;
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::SendMsg(const Replay &msg, bool isLastMsg)
{
    if (oping_ == 0)
    {
        if (write_list_.size() == 0)
        {
            OpWrite(msg, isLastMsg);
        }
        else
        {
            write_list_.push_back(WriteInfo{.Rep = msg, .IsLastMsg = isLastMsg});
            OpWrite();
        }
    }
    else
    {
        write_list_.push_back(WriteInfo{.Rep = msg, .IsLastMsg = isLastMsg});
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::SendMsgWithCopy(const Replay &msg, bool isLastMsg)
{
    if (oping_ == 0)
    {
        if (write_list_.size() == 0)
        {
            OpWrite(msg, isLastMsg);
        }
        else
        {
            Replay v;
            v.CopyFrom(msg);
            write_list_.push_back(WriteInfo{.Rep = msg, .IsLastMsg = isLastMsg});
            OpWrite();
        }
    }
    else
    {
        write_list_.push_back(WriteInfo{.Rep = msg, .IsLastMsg = isLastMsg});
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpRead()
{
    oping_ = 1;
    request_.Clear();
    stream_.Read(&request_, (T *)this);
    SetStatus(PROCESS);
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite(const Replay &rep, bool isLastMsg)
{
    oping_ = 1;
    stream_.Write(rep, (T *)this);
    if (!isLastMsg)
    {
        SetStatus(WRITE);
    }
    else
    {
        SetStatus(READ);
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::OpWrite()
{
    if (write_list_.size() > 0)
    {
        auto &r = write_list_.front();
        OpWrite(r.Rep, r.IsLastMsg);
        write_list_.pop_front();
    }
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
