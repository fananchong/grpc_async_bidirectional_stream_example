#include "tag.hpp"
#include "msg.hpp"
#include "util.hpp"

void Tag::Release(IMsg *v)
{
    v->Release();
    delays_.push_back({v, get_current_time_nanos()});
}

void Tag::DelayDel()
{
    if (delays_.size() == 0)
    {
        return;
    }
    auto now = get_current_time_nanos();
    while (delays_.size() != 0)
    {
        auto &v = delays_.front();
        if ((now - v.time_) / 1000 / 1000 / 1000 > 60)
        {
            delete v.obj;
            delays_.pop_front();
        }
        else
        {
            break;
        }
    }
}