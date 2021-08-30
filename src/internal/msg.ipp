#include "log.hpp"

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::StreamBase(Service *service, ServerImpl *server, grpc::ServerCompletionQueue *cq)
    : service_(service), server_(server), cq_(cq), stream_(&ctx_), status_(CREATE), closed_(false)
{
}

template <class T, class Service, class Replay, class Request>
StreamBase<T, Service, Replay, Request>::~StreamBase()
{
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq)
{
    gtags.Set(new T(service_, server, cq));
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
        Accpet(server_, cq_);
    case READ:
        reply_.Clear();
        stream_.Read(&request_, (T *)this);
        status_ = WRITE;
        break;
    case WRITE:
        OnProcess();
        stream_.Write(reply_, (T *)this);
        if (!closed_)
        {
            status_ = READ;
        }
        else
        {
            INFO("closed_=true, id={}", id_);
            status_ = FINISH;
        }
        request_.Clear();
        break;
    case FINISH:
        INFO("status_=FINISH, id={}", id_);
        OnExit();
        ctx_.TryCancel();
        status_ = CLOSED;
        break;
    case CLOSED:
        INFO("status_=CLOSED, id={}", id_);
    }
}

template <class T, class Service, class Replay, class Request>
void StreamBase<T, Service, Replay, Request>::Release()
{
    INFO("status_={}, id={}", status_, id_);
    OnExit();
    stream_.Finish(grpc::Status::CANCELLED, (T *)(this));
    status_ = CLOSED;
}

template <class T, class Service, class Replay, class Request>
UnitaryBase<T, Service, Replay, Request>::UnitaryBase(Service *service, ServerImpl *server, grpc::ServerCompletionQueue *cq)
    : service_(service), server_(server), cq_(cq), responder_(&ctx_), status_(CREATE)
{
}

template <class T, class Service, class Replay, class Request>
UnitaryBase<T, Service, Replay, Request>::~UnitaryBase()
{
}

template <class T, class Service, class Replay, class Request>
void UnitaryBase<T, Service, Replay, Request>::Accpet(ServerImpl *server, grpc::ServerCompletionQueue *cq)
{
    gtags.Set(new T(service_, server, cq));
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
        Accpet(server_, cq_);
        ret = OnProcess();
        status_ = FINISH;
        responder_.Finish(reply_, ret, (T *)this);
        break;
    default:
        GPR_ASSERT(status_ == FINISH);
        gtags.Release((T *)this);
        break;
    }
}
