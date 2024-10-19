#include "webserver.h"

#define PATH "./log_data"

int WebServer::setfd_nonblock(int fd)
{
    assert(fd > 0);
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
} 

bool WebServer::init_socket()
{
    int ret;
    struct sockaddr_in addr;
    if(m_port > 65535 || m_port < 1024)
    {
        LOG_ERROR("Port: %d is error!", m_port);
        return false;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(m_port);
    struct linger optlinger = { 0} ;
    if(open_linger)
    {
        optlinger.l_onoff = 1;
        optlinger.l_linger = 1;
    }
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        LOG_ERROR("create socket error!");
        return false;
    }
    ret = setsockopt(listen_fd, SOL_SOCKET, SO_LINGER, &optlinger, sizeof(optlinger));
    if(ret < 0)
    {
        LOG_ERROR("the optlinger init error!");
        close(listen_fd);
        return false;
    }
    int optval = 1;
    ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
    if(ret == -1)
    {
        LOG_ERROR("the socket setsockopt error!");
        close(listen_fd);
        return false;
    }
    ret = bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        LOG_ERROR("bind the port: %d error!", m_port);
        close(listen_fd);
        return false;
    }
    ret = listen(listen_fd, 6);
    if(ret < 0)
    {
        LOG_ERROR("listen port: %d error!", m_port);
        close(listen_fd);
        return false;
    }
    ret = m_epoller->add_fd(listen_fd, listen_event | EPOLLIN);
    if(ret == 0)
    {
        LOG_ERROR("add listenfd to epoller error!");
        close(listen_fd);
        return false;
    }
    setfd_nonblock(listen_fd);
    LOG_INFO("the server port: %d init successful", m_port);
    return true;
}

void WebServer::init_event_mode(int trig_mode)
{
    listen_event = EPOLLRDHUP;
    conn_event = EPOLLONESHOT | EPOLLRDHUP;
    switch (trig_mode)
    {
    case 0:
        break;
    case 1:
        conn_event |= EPOLLET;
        break;
    case 2:
        listen_event |= EPOLLET;
        break;
    case 3:
        listen_event |= EPOLLET;
        conn_event |= EPOLLET;
        break;
    default:
        listen_event |= EPOLLET;
        conn_event |= EPOLLET;
        break;
    }
    HttpConn::is_ET = (conn_event & EPOLLET);
}

void WebServer::close_conn(HttpConn* client)
{
    assert(client);
    LOG_INFO("client[%d] quit !",client->get_fd());
    m_epoller->del_fd(client->get_fd());
    client->close_conn();
}

void WebServer::send_error(int fd, const char* info)
{
    assert(fd > 0);
    int ret = send(fd, info, sizeof(info), 0);
    if(ret < 0)
    {
        LOG_ERROR("send info to client[%d] error!", fd);
    }
    close(fd);
}

void WebServer::extent_time(HttpConn* client)
{
    assert(client);
    if(m_timeout_ms > 0) m_timer->adjust(client->get_fd(), m_timeout_ms);
}

void WebServer::add_client(int fd, sockaddr_in addr)
{
    assert(fd > 0);
    m_user[fd].init(fd, addr);
    if(m_timeout_ms > 0)
    {
        m_timer->add(fd, m_timeout_ms, std::bind(&WebServer::close_conn, this, &m_user[fd]));
    }
    m_epoller->add_fd(fd, EPOLLIN | conn_event);
    setfd_nonblock(fd);
    LOG_INFO("client[%d] join in!", m_user[fd].get_fd());
}

void WebServer::deal_listen()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    do
    {
        int fd = accept(listen_fd, (struct sockaddr *)&addr, &len);
        if(fd < 0) return;
        else if(HttpConn::user_count >= MAX_FD)
        {
            send_error(fd, "the WebServer");
            LOG_WARN("clients has full!");
            return;
        }
        add_client(fd, addr);
    } while (listen_event & EPOLLET);
}

void WebServer::on_process(HttpConn* client)
{
    if(client->process()) m_epoller->mod_fd(client->get_fd(), conn_event | EPOLLOUT);
    else m_epoller->mod_fd(client->get_fd(), conn_event | EPOLLIN); 
}

void WebServer::on_read(HttpConn* client)
{
    assert(client);
    int ret = 1;
    int read_errno = 0;
    ret = client->read(&read_errno);
    if(ret <= 0 && read_errno != EAGAIN)
    {
        close_conn(client);
        return;
    }
    on_process(client);
}

void WebServer::on_write(HttpConn* client)
{
    assert(client);
    int ret = 1; 
    int write_errno = 0;
    ret = client->write(&write_errno);
    if(client->to_write_bytes() == 0)
    {
        if(client->is_keep_alive())
        {
            on_process(client);
            return;
        }
    }
    else if(ret < 0)
    {
        if(write_errno == EAGAIN)
        {
            m_epoller->mod_fd(client->get_fd(), conn_event | EPOLLOUT);
            return;
        }
    }
    close_conn(client);
}

void WebServer::deal_read(HttpConn* client)
{
    assert(client);
    extent_time(client);
    m_threadpool->addTask(std::bind(&WebServer::on_read, this, client));
}

void WebServer::deal_write(HttpConn* client)
{
    assert(client);
    extent_time(client);
    m_threadpool->addTask(std::bind(&WebServer::on_write, this, client));
}

WebServer::WebServer(int port, int sql_port, const char* sql_user, const char* sql_pwd, 
                                const char* db_name, int connpool_num, int thread_num, bool open_log, 
                                int log_quesize, int trig_mode, int timeout_ms, bool opt_linger):
                                m_port(port), m_timeout_ms(timeout_ms), open_linger(opt_linger), is_close(false),
                                m_epoller(new Epoller()), m_timer(new Timer()), m_threadpool(new ThreadPool(thread_num))
{
    m_src_dir = getcwd(nullptr, 256);
    assert(m_src_dir);
    strncat(m_src_dir, "/resources/", 16);
    HttpConn::user_count = 0;
    HttpConn::src_dir = m_src_dir;
    SqlConnPool::get_instance()->init("localhost", sql_port, sql_user, sql_pwd, db_name, connpool_num);
    init_event_mode(trig_mode);
    if(open_log)
    {
        Log::get_instance()->init(PATH, "webserver.log", log_quesize);
        LOG_INFO("%d ======= the log init  success =======", log_quesize);
        if(!init_socket()) is_close = true;
        if(is_close) {LOG_ERROR("======= the WebServer init error! =======");}
        else
        {
            LOG_INFO("%d  ======= the WebServer init  info =======", log_quesize);
            LOG_INFO("Port: %d, OpenLinger: %s ", m_port, open_linger? "true" : "false");
            LOG_INFO("Listen Mode: %s, OpenConn Mode: %s",
                                     listen_event & EPOLLET? "ET" : "LT",conn_event & EPOLLET? "ET" : "LT");
            LOG_INFO("src_Dir: %s", HttpConn::src_dir);
            LOG_INFO("SqlConnPool num: %d, ThreadPool num: %d", connpool_num, thread_num);
        }
    }
}

void WebServer::start()
{
    int time_ms = -1;
    if(!is_close) { LOG_INFO("======= the WebServer start ======="); }
    while (!is_close)
    {
        if(m_timeout_ms > 0) m_timer->get_next_tick();
        int event_cnt = m_epoller->wait(m_timeout_ms);
        for(int i = 0;i < event_cnt;i++)
        {
            int fd = m_epoller->get_event_fd(i);
            uint32_t events = m_epoller->get_epoll_events(i);
            if(fd == listen_fd) deal_listen();
            else if(events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                assert(m_user.count(fd) > 0);
                close_conn(&m_user[fd]);
            }
            else if(events & EPOLLIN)
            {
                assert(m_user.count(fd) > 0);
                deal_read(&m_user[fd]);
            }
            else if (events & EPOLLOUT)
            {
                assert(m_user.count(fd) > 0);
                deal_write(&m_user[fd]);
            }
            else { LOG_ERROR("Unrecognized event!"); }
        }
    }
}

WebServer::~WebServer()
{
    close(listen_fd);
    is_close = true;
    free(m_src_dir);
    SqlConnPool::get_instance()->close_conn();
}