#ifndef  HTTPCONN_H
#define HTTPCONN_H

#include <atomic>
#include <sys/types.h>
#include <sys/uio.h>     // readv/writev
#include <arpa/inet.h>   // sockaddr_in
#include <stdlib.h>      // atoi()
#include <errno.h>       // 错误码定义

#include "../log/log.h"
#include "../buffer/buffer.h"
#include "../pool/sqlconnRAII.h"
#include "httprequest.h"
#include "httpresponse.h"

class HttpConn
{
public:
    // static const int READ_BUFFER_SIZE = 4096;
    // static const int WRITE_BUFFER_SIZE = 2048;
    static bool is_ET;
    static const char* src_dir;
    static std::atomic<int> user_count;
    HttpConn();
    void init(int sockfd, sockaddr_in& addr);
    void close_conn();
    int get_fd() const;
    sockaddr_in get_addr() const;
    int get_port() const;
    const char* get_ip() const;
    ssize_t read(int* save_errno);
    ssize_t write(int* save_erno);
    bool process();
    int to_write_bytes() { return m_iov[0].iov_len + m_iov[1].iov_len; }
    bool is_keep_alive() const { return m_request.is_keep_alive(); }
    ~HttpConn();
private:
    int m_fd;
    struct sockaddr_in m_addr;
    bool is_close;
    int iov_cnt;
    struct iovec m_iov[2];
    Buffer read_buff;
    Buffer write_buff;
    HttpRequest m_request;
    HttpResponse m_response;
};

#endif