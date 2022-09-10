#include "tag.hpp"
#include "msg.hpp"
#include "util.hpp"

void Tag::Release(const std::shared_ptr<IMsg> &v)
{
    v->Release();
    delays_.push_back({v, get_current_time_nanos()});
}

void Tag::DelayDel(int64_t now)
{
    if (delays_.size() == 0)
    {
        return;
    }
    while (delays_.size() != 0)
    {
        auto &v = delays_.front();
        if ((now - v.time_) / 1000000000 > 600)
        {
            delays_.pop_front();
        }
        else
        {
            break;
        }
    }
}
