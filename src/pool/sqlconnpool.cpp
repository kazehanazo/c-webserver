#include "./sqlconnpool.h"

SqlConnPool::SqlConnPool()
{
    free_count = 0;
    use_count = 0;
}

void SqlConnPool::init(const char* host, int port, const char* user, const char* pwd, const char* dbname, int conn_size)
{
    assert(conn_size > 0);
    for(int i = 0;i < conn_size;i++)
    {
        MYSQL *sql = nullptr;
        sql = mysql_init(sql);
        if(!sql)
        {
            LOG_ERROR("the sql init error!");
            assert(sql);
        }
        sql = mysql_real_connect(sql, host, user, pwd, dbname, port, nullptr, 0);
        if(!sql)
        {
            LOG_ERROR("the sql connection error!");
            assert(sql);
        }
        conn_queue.push(sql);
        free_count++;
    }
    max_size = conn_size;
    sem_init(&m_sem, 0, max_size );
}
MYSQL* SqlConnPool::get_conn()
{
    MYSQL *sql = nullptr;
    if(conn_queue.empty())
    {
        LOG_WARN("the sql connection pool is empty!");
        return nullptr;
    }
    sem_wait(&m_sem);
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        sql = conn_queue.front();
        conn_queue.pop();
    }
    return sql;
}
void SqlConnPool::release_conn(MYSQL* sql)
{
    assert(sql);
    std::lock_guard<std::mutex> locker(m_mutex);
    conn_queue.push(sql);
    sem_post(&m_sem);
}
int SqlConnPool::get_free_count()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return conn_queue.size();
}
void SqlConnPool::close_conn()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    while(!conn_queue.empty())
    {
        auto sql = conn_queue.front();
        conn_queue.pop();
        mysql_close(sql);
    }
    mysql_library_end();
}
SqlConnPool::~SqlConnPool()
{
    close_conn();
}
