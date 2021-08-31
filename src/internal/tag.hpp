#pragma once

#include <list>
#include <stdint.h>
#include <cinttypes>

class IMsg;

class Tag
{
public:
    Tag() {}
    ~Tag() {}

    void Release(IMsg *v);
    void DelayDel();

private:
    struct delayDelItem
    {
        IMsg *obj;
        int64_t time_;
    };
    std::list<delayDelItem> delays_;
};
