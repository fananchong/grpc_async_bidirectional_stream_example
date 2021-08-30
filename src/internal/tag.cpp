#include "tag.hpp"
#include "msg.hpp"

void Tag::Set(IMsg *v)
{
    objs_[v->ID()] = v;
}

IMsg *Tag::Get(int64_t id)
{
    auto it = objs_.find(id);
    if (it != objs_.end())
    {
        return it->second;
    }
    return nullptr;
}

void Tag::Release(IMsg *v)
{
    auto it = objs_.find(v->ID());
    if (it != objs_.end())
    {
        delete it->second;
        objs_.erase(it);
    }
}
