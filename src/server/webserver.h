#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <unordered_map>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "epoller.h"
#include "../http/httpconn.h"
#include "../log/log.h"
#include "../pool/threadpool.h"
#include "../pool/sqlconnpool.h"
#include "../pool/sqlconnRAII.h"
#include "../timer/timer.h"

class WebServer
{
private:
    int m_port;
    int listen_fd;
    int m_timeout_ms;
    char* m_src_dir;
    bool is_close;
    bool open_linger;
    uint32_t conn_event;
    uint32_t listen_event;
    std::unique_ptr<Epoller> m_epoller;
    std::unique_ptr<ThreadPool> m_threadpool;
    std::unique_ptr<Timer> m_timer;
    std::unordered_map<int, HttpConn> m_user;

    static const int MAX_FD = 65536;
    static int setfd_nonblock(int fd);

    bool init_socket();
    void init_event_mode(int trig_mode);
    void close_conn(HttpConn* client);
    void send_error(int fd, const char* info);
    void extent_time(HttpConn* client);
    void add_client(int fd, sockaddr_in addr);
    void deal_listen();
    void on_process(HttpConn* client);
    void on_read(HttpConn* client);
    void on_write(HttpConn* client);
    void deal_read(HttpConn* client);
    void deal_write(HttpConn* client);

public:
    WebServer(int port, int sql_port, const char* sql_user, const char* sql_pwd, 
                                const char* db_name, int connpool_num, int thread_num, bool open_log, 
                                int log_quesize, int trig_mode, int timeout_ms, bool opt_linger);
    void start();
    ~WebServer();
};


#endif