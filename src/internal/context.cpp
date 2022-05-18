#include "context.hpp"
#include "msg.hpp"
#include "tag.hpp"
#include "util.hpp"

HandleRpcsContext::HandleRpcsContext()
    : tags_(new Tag())
{
}

HandleRpcsContext::~HandleRpcsContext()
{
}

void HandleRpcsContext::Update(const std::function<int(void)> &fn)
{
    auto t1 = get_current_time_nanos();
    int msg_count = fn();
    auto t2 = get_current_time_nanos();
    int64_t interval = INTERVAL_MS * 1000000; // 转为纳秒
    auto fragment2 = t2 / interval;
    current_fragment_ = fragment2;
}

void HandleRpcsContext::OnTrigger()
{
    for (auto v : streams_)
    {
        ((IMsg *)v)->OnTrigger();
    }
}