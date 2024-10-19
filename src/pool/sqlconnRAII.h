#ifndef SQLCONNRAII_H
#define SQLCONNRAII_H

#include "sqlconnpool.h"
class SqlConnRAII
{
private:
    MYSQL* m_sql;
    SqlConnPool* m_conn_pool;
public:
    SqlConnRAII(MYSQL** sql, SqlConnPool *conn_pool)
    {
        assert(conn_pool);
        *sql = conn_pool->get_conn();
        m_sql = *sql;
        m_conn_pool = conn_pool;
    }
    ~SqlConnRAII()
    {
        if(m_sql) m_conn_pool->release_conn(m_sql);
    }
};

#endif