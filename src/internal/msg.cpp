#include "msg.hpp"

static std::atomic<int64_t> gid(0);

int64_t gen_id()
{
    return ++gid;
}
