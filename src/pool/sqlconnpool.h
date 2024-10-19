#ifndef SQLCONNPOLL_H
#define SQLCONNPOLL_H

#include <mutex>
#include <string>
#include <queue>
#include <thread>
#include <mysql/mysql.h>
#include <semaphore.h>
#include <assert.h>
#include "../log/log.h"

class SqlConnPool
{
private:
    SqlConnPool();
    ~SqlConnPool();

    int max_size;
    int free_count;
    int use_count;
    std::queue<MYSQL *> conn_queue;
    std::mutex m_mutex;
    sem_t m_sem;
public:
    static SqlConnPool *get_instance()
    {
        static SqlConnPool instance;
        return &instance;
    }
    MYSQL* get_conn();
    void release_conn(MYSQL *sql);
    int get_free_count();
    void init(const char* host, int port, const char* user, const char* pwd, const char* dbname, int conn_size);
    void close_conn();
};


#endif