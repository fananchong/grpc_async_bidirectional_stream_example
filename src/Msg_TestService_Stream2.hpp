#pragma once

#include "internal/msg.hpp"
#include "proto/test.pb.h"
#include "proto/test.grpc.pb.h"
#include <spdlog/fmt/fmt.h>
#include <atomic>

// STREAM_MESSAGE(MSG, SERVICE, ACK, REQ, ...)
STREAM_MESSAGE(
    Msg_TestService_Stream2, test::TestService::AsyncService, test::Frame, test::Frame,
    // 私有成员
    //
);

void Msg_TestService_Stream2::OnCreate()
{
    DEBUG("Create Stream, id={}", id_);
    service_->RequestStream2(&ctx_, &stream_, cq_, cq_, this);
}

void Msg_TestService_Stream2::OnProcess()
{
    INFO("Msg_TestService_Stream2::OnProcess");
    switch (request_->Msg_case())
    {
    case test::Frame::kEcho:
    {
        auto rep1 = std::make_shared<test::Frame>();
        auto v1 = rep1->mutable_echo();
        v1->set_data(fmt::format("{} #1", request_->echo().data()));
        SendMsg(rep1);

        auto rep2 = std::make_shared<test::Frame>();
        auto v2 = rep2->mutable_echo();
        v2->set_data(fmt::format("{} #2", request_->echo().data()));
        SendMsg(rep2);

        auto rep3 = std::make_shared<test::Frame>();
        auto v3 = rep3->mutable_echo();
        v3->set_data(fmt::format("{} #3", request_->echo().data()));
        SendMsg(rep3);
    }
    break;
    case test::Frame::kPing:
        break;
    default:
        break;
    }
}

void Msg_TestService_Stream2::OnExit()
{
    DEBUG("Close Steam, id={}", id_);
}
