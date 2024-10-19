#include "httpconn.h"

bool HttpConn::is_ET;
const char* HttpConn::src_dir;
std::atomic<int> HttpConn::user_count;

HttpConn::HttpConn()
{
    m_fd = -1;
    m_addr = { 0 };
    is_close = true;
}

void HttpConn::init(int sockfd, sockaddr_in& addr)
{
    assert(sockfd > 0);
    user_count++;
    m_fd = sockfd;
    m_addr = addr;
    is_close = false;
    write_buff.retrieve_all();
    read_buff.retrieve_all();
    LOG_INFO("Clinet[%d](%s:%d) join, user_count: %d", m_fd, get_ip(), get_port(), (int)user_count);
}

void HttpConn::close_conn()
{
    m_response.umap_file();
    if(is_close == false)
    {
        is_close = true;
        user_count--;
        close(m_fd);
        LOG_INFO("Clinet[%d](%s:%d) quit, user_count: %d", m_fd, get_ip(), get_port(), (int)user_count);
    }
}

int HttpConn::get_fd() const
{
    return m_fd;
}

sockaddr_in HttpConn::get_addr() const
{
    return m_addr;
}

int HttpConn::get_port() const
{
    return m_addr.sin_port;
}

const char* HttpConn::get_ip() const
{
    return inet_ntoa(m_addr.sin_addr);
}

ssize_t HttpConn::read(int *save_errno)
{
    ssize_t len = -1;
    do
    {
        len = read_buff.read_fd(m_fd, save_errno);
        if(len <= 0)
        {
            *save_errno = errno;
            break;
        }
    } while (is_ET);
    return len;
}

ssize_t HttpConn::write(int *save_errno)
{
    ssize_t len = -1;
    do
    {
        len = writev(m_fd, m_iov, iov_cnt);
        if(len <= 0)
        {
            *save_errno = errno;
            break;
        }
        if(m_iov[0].iov_len + m_iov[1].iov_len  == 0) break;
        else if(static_cast<size_t>(len) > m_iov[0].iov_len)
        {
            m_iov[1].iov_base = (uint8_t*)m_iov[1].iov_base + (len - m_iov[0].iov_len);
            m_iov[1].iov_len = len - m_iov[0].iov_len;
            if(m_iov[0].iov_len)
            {
                write_buff.retrieve_all();
                m_iov->iov_len = 0;
            }
        }
        else
        {
            m_iov[0].iov_base = (uint8_t*)m_iov[0].iov_base +len;
            m_iov[0].iov_len -= len;
            write_buff.retrieve(len);
        }
    } while (is_ET || to_write_bytes() > 10240);
    return len;
}

bool HttpConn::process()
{
    m_request.init();
    if(read_buff.readable_bytes() <= 0) return false;
    else if(m_request.parse(read_buff))
    {
        LOG_DEBUG("%s", m_request.path().c_str());
        m_response.init(src_dir, m_request.path(), m_request.is_keep_alive(), 200);
    }
    else  m_response.init(src_dir, m_request.path(), false, 400);
    m_response.do_response(write_buff);
    m_iov[0].iov_base = const_cast<char*>(write_buff.peek());
    m_iov[0].iov_len = write_buff.readable_bytes();
    iov_cnt = 1;
    if(m_response.file() && m_response.flie_len() > 0)
    {
        m_iov[1].iov_base = m_response.file();
        m_iov[1].iov_len = m_response.flie_len();
        iov_cnt = 2;
    }
    LOG_DEBUG("file_size: %d, %d to %d",m_response.flie_len(), iov_cnt, to_write_bytes());
    return true;
}
HttpConn::~HttpConn()
{
    close_conn();
}