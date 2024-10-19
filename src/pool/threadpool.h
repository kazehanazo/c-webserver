#ifndef THREADPOOL_H
#define THREADPOOL_H    

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <cassert>

class ThreadPool
{
private:
    struct Pool
    {
        std::mutex m_mutex;
        std::condition_variable m_cond;
        std::queue<std::function<void()>> tasks;
        bool isClosed;
    };
    std::shared_ptr<Pool> m_pool;
public:
    explicit ThreadPool(size_t threadcount = 7): m_pool(std::make_shared<Pool>())
    {
        assert(threadcount > 0);
        for(size_t i = 0; i < threadcount; i++)
        {
            std::thread([pool = m_pool]
            {
                std::unique_lock<std::mutex> locker(pool->m_mutex);
                while(true)
                {
                    if(!pool->tasks.empty())
                    {
                        auto task = std::move(pool->tasks.front());
                        pool->tasks.pop();
                        locker.unlock();
                        task();
                        locker.lock();
                    }
                    else if(pool->isClosed) break;
                    else pool->m_cond.wait(locker);
                }
            }).detach();
        }
    }
    ThreadPool() = default;
    ThreadPool(ThreadPool&&) = default;
    template<class F>
    void addTask(F&& task)
    {
        {
            std::lock_guard<std::mutex> locker(m_pool->m_mutex);
            m_pool->tasks.emplace(std::forward<F>(task));
        }
        m_pool->m_cond.notify_one();
    }
    ~ThreadPool()
    {
        if(static_cast<bool>(m_pool))
        {
            std::lock_guard<std::mutex> locker(m_pool->m_mutex);
            m_pool->isClosed = true;
        }
        m_pool->m_cond.notify_all();
    }
};

#endif