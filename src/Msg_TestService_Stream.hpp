#pragma once

#include "internal/msg.hpp"
#include "proto/test.pb.h"
#include "proto/test.grpc.pb.h"
#include <spdlog/fmt/fmt.h>
#include <atomic>

// STREAM_MESSAGE(MSG, SERVICE, ACK, REQ, ...)
STREAM_MESSAGE(
    Msg_TestService_Stream, test::TestService::AsyncService, test::Frame, test::Frame,
    // 私有成员
    //
);

void Msg_TestService_Stream::OnCreate()
{
    DEBUG("Create Stream, id={}", id_);
    service_->RequestStream(&ctx_, &stream_, cq_, cq_, this);
}

void Msg_TestService_Stream::OnProcess()
{
    switch (request_.Msg_case())
    {
    case test::Frame::kEcho:
    {
        auto v = reply_.mutable_echo();
        v->set_data(request_.echo().data());
        // CloseStream();
    }
    break;
    }
}

void Msg_TestService_Stream::OnExit()
{
    INFO("Close Steam, id={}", id_);
}
