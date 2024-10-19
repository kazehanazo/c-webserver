#ifndef TIMER_H
#define TIMER_H

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <time.h>
#include <assert.h>
#include <arpa/inet.h>

#include "../log/log.h"

typedef std::function<void()> TimeoutCallBack;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds MS;
typedef Clock::time_point TimeStamp;

struct TimeNode
{
    int id;
    TimeStamp expires;
    TimeoutCallBack cb;
    bool operator<(const TimeNode& t)
    {
        return expires < t.expires;
    }
};

class Timer
{
private:
    std::vector<TimeNode> m_heap;
    std::unordered_map<int, size_t> m_ref;
    void swap_node(size_t i, size_t j);
    void sift_up(size_t i);
    bool sift_down(size_t idx, size_t n);
    void del_node(size_t idx);

public:
    Timer() { m_heap.reserve(64); }
    void adjust(int id, int timeout);
    void add(int id, int timeout, const TimeoutCallBack &cb);
    void pop();
    void do_work(int id);
    void tick();
    int get_next_tick();
    void clear();
    ~Timer() {clear(); }
};

#endif