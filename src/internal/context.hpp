#pragma once

#include <map>
#include <set>
#include <functional>
#include <memory>

// HandleRpcsContext gRPC 事件处理上下文

class Tag;

class HandleRpcsContext
{
public:
    HandleRpcsContext();
    ~HandleRpcsContext();

    void Update(const std::function<int(void)> &fn); // 更新上下文信息
    void OnTrigger();                                // 按时间片段推进，被触发

public:
    const int64_t INTERVAL_MS = 50; // 把时间轴按固定间隔切分，单位毫秒 milliseconds
    int64_t current_fragment_ = 0;  // 当前时间片段
    std::set<void *> streams_;      // 当前所有流对象
    std::unique_ptr<Tag> tags_;     // 管理所有 tag 对象，延迟删除
};
