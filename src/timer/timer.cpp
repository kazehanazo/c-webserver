#include "timer.h"

void Timer::swap_node(size_t i, size_t j)
{
    assert(i >= 0 && i < m_heap.size());
    assert(j >= 0 && j < m_heap.size());
    std::swap(m_heap[i], m_heap[j]);
    m_ref[m_heap[i].id] = j;
    m_ref[m_heap[j].id] = i;
    
}

void Timer::sift_up(size_t i)
{
    assert(i >= 0 && i < m_heap.size());
    size_t j = (i - 1) / 2;
    while (j >= 0)
    {
        if(m_heap[j] < m_heap[i]) break;
        swap_node(i, j);
        i = j;
        j = (i - 1) / 2;
    }
}

bool Timer::sift_down(size_t idx, size_t n)
{
    assert(idx >= 0 && idx < m_heap.size());
    assert(n >= 0 && n <= m_heap.size());
    size_t i = idx;
    size_t j = i * 2 + 1;
    while (j < n)
    {
        if(j + 1 < n && m_heap[j + 1] < m_heap[j]) j++;
        if(m_heap[i] < m_heap[j]) break;
        swap_node(i, j);
        i = j;
        j = i * 2 + 1;
    }
    return i > idx;
}

void Timer::del_node(size_t idx)
{
    assert(!m_heap.empty() && idx >= 0 && idx < m_heap.size());
    size_t i = idx;
    size_t n = m_heap.size() - 1;
    assert(i <= n);
    if(i < n)
    {
        swap_node(i, n);
        if(!sift_down(i , n)) sift_up(i);
    }
    m_ref.erase(m_heap.back().id);
    m_heap.pop_back();
}

void Timer::adjust(int id, int timeout)
{
    assert(!m_heap.empty() && m_ref.count(id) > 0);
    m_heap[m_ref[id]].expires = Clock::now() + MS(timeout);
    if(!sift_down(m_ref[id], m_heap.size())) sift_up(m_ref[id]);
}

void Timer::add(int id, int timeout, const TimeoutCallBack &cb)
{
    assert(id >= 0);
    size_t i;
    if(m_ref.count(id) == 0)
    {
        i = m_heap.size();
        m_heap.push_back({id, Clock::now() + MS(timeout), cb});
        m_ref[id] = i;
        sift_up(i);
    }
    else
    {
        i = m_ref[id];
        m_heap[i].expires = Clock::now() + MS(timeout);
        m_heap[i].cb = cb;
        if(!sift_down(i, m_heap.size())) sift_up(i);
    }
}

void Timer::pop()
{
    assert(!m_heap.empty());
    del_node(0);
}

void Timer::do_work(int id)
{
    if(m_heap.empty() || m_ref.count(id) == 0) return;
    size_t i = m_ref[id];
    TimeNode node = m_heap[i];
    node.cb();
    del_node(i);
}

void Timer::tick()
{
    if(m_heap.empty()) return;
    while (!m_heap.empty())
    {
        TimeNode node = m_heap.front();
        if(std::chrono::duration_cast<MS>(node.expires - Clock::now()).count() > 0) break;
        node.cb();
        pop();
    }
}

int Timer::get_next_tick()
{
    tick();
    size_t ret = -1;
    if(!m_heap.empty())
    {
        ret = std::chrono::duration_cast<MS>(m_heap.front().expires - Clock::now()).count();
        if(ret < 0) ret = 0;
    }
    return ret;
}

void Timer::clear()
{
    m_heap.clear();
    m_ref.clear();
}