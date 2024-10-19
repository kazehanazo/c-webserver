#ifndef BLOCKQUEUE_H
#define BLOCKQUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include<cassert>
#include <sys/time.h>

template<class T>
class BlockQueue
{
private:
    std::deque<T> m_deque;
    size_t m_size;
    std::mutex m_mutex;
    bool is_close;
    std::condition_variable cond_consumer;
    std::condition_variable cond_producer;
public:
    explicit BlockQueue(size_t max_size = 1000);
    T front();
    T back();
    void push_back(const T &item);
    void push_front(const T &item);
    bool pop (T &item);
    bool pop (T &item, int timeout);
    size_t size();
    size_t max_size();
    bool empty();
    bool full();
    void clear();
    void flush();
    void close();
    ~BlockQueue();
};
template<class T>
BlockQueue<T>::BlockQueue(size_t max_size): m_size(max_size)
{
    assert(max_size > 0);
    is_close = false;
}
template<class T>
T BlockQueue<T>::front()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_deque.front();
}
template<class T>
T BlockQueue<T>::back()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_deque.back();
}
template<class T>
void BlockQueue<T>::push_back(const T &item)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    while(m_deque.size() >= m_deque.max_size())
    {
        cond_producer.wait(locker);
    }
    m_deque.push_back(item);
    cond_consumer.notify_one();
}
template<class T>
void BlockQueue<T>::push_front(const T &item)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    while(m_deque.size() >= max_size())
    {
        cond_producer.wait(locker);
    }
    m_deque.push_front(item);
    cond_consumer.notify_one();
}
template<class T>
bool BlockQueue<T>::pop(T &item)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    while(m_deque.empty())
    {
        cond_consumer.wait(locker);
        if(is_close) return false;
    }
    item = m_deque.front();
    m_deque.pop_front();
    cond_producer.notify_one();
}
template<class T>
bool BlockQueue<T>::pop(T &item, int timeout)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    while(m_deque.empty())
    {
        if (cond_consumer.wait_for(locker, std::chrono::seconds(timeout)) == std::cv_status::timeout)  return false;
        if(is_close) return false;
    }
    item = m_deque.front();
    m_deque.pop_front();
    cond_consumer.notify_one();
}
template<class T>
size_t BlockQueue<T>::size()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_deque.size();
}
template<class T>
size_t BlockQueue<T>::max_size()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_size;
}
template<class T>
bool BlockQueue<T>::empty()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_deque.empty();
}
template<class T>
bool BlockQueue<T>::full()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_deque.size() >= m_size;
}
template<class T>
void BlockQueue<T>::clear()
{
    std::lock_guard<std::mutex> locker(m_mutex);
   m_deque.clear();
}
template<class T>
void BlockQueue<T>::flush()
{
    cond_consumer.notify_one();
}
template<class T>
void BlockQueue<T>::close()
{
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_deque.clear();
        is_close = true;
    }
    cond_consumer.notify_all();
    cond_producer.notify_all();
}
template<class T>
BlockQueue<T>::~BlockQueue()
{
    close();
}

#endif