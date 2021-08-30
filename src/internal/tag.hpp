#pragma once

#include <unordered_map>

class IMsg;

class Tag
{
public:
    Tag() {}
    ~Tag() {}

    void Set(IMsg *v);
    IMsg *Get(int64_t id);
    void Release(IMsg *v);

private:
    std::unordered_map<int64_t, IMsg *> objs_;
};
