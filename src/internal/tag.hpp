#pragma once

#include <list>
#include <stdint.h>
#include <cinttypes>
#include <memory>

class IMsg;

class Tag
{
public:
    Tag() {}
    ~Tag() {}

    void Release(const std::shared_ptr<IMsg> &v);
    void DelayDel(int64_t now);

private:
    struct delayDelItem
    {
        std::shared_ptr<IMsg> obj;
        int64_t time_;
    };
    std::list<delayDelItem> delays_;
};
