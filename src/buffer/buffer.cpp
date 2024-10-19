#include "buffer.h"

Buffer::Buffer(int buff_size): m_buffer(buff_size), read_pos(0), write_pos(0), is_full(false) {}

char* Buffer::begin_ptr()
{
    return m_buffer.data();
}

const char* Buffer::begin_ptr() const
{
    return m_buffer.data();
}

size_t Buffer::readable_bytes() const
{
    return  is_full ? m_buffer.size() - read_pos + write_pos : write_pos - read_pos;
}

size_t Buffer::writable_bytes() const
{
    return m_buffer.size() -readable_bytes();
}

size_t Buffer::prependable_bytes() const
{
    return read_pos;
}

const char* Buffer::peek() const
{
    return begin_ptr() + read_pos;
}

void Buffer::retrieve(size_t len)
{
    assert(len <= readable_bytes());
    if(read_pos + len >= m_buffer.size()) is_full = false;
    read_pos = (read_pos + len) % m_buffer.size();
}

void Buffer::retrieve_until(const char* end)
{
    //assert(end - begin_ptr() > m_buffer.size());
    if(end > peek()) retrieve(end - peek());
    else retrieve(m_buffer.size() - read_pos + (end - begin_ptr()));
}

void Buffer::retrieve_all()
{
    //bzero(&m_buffer, m_buffer.size());
    write_pos = 0;
    read_pos = 0;
    is_full = false;
}

std::string Buffer::retrieve_to_str()
{
    std::string str;
    str.reserve(readable_bytes());
    if(is_full) 
    {
        str.append(peek(), m_buffer.size() - read_pos);
        str.append(begin_ptr(), write_pos);
    }
    else str.append(peek(), readable_bytes());
    retrieve_all();
    return str;
}

const char* Buffer::begin_write_const() const
{
    return begin_ptr() + write_pos;
}

char* Buffer::begin_write()
{
    return begin_ptr() + write_pos;
}

void Buffer::has_written(size_t len)
{
    if(write_pos + len >= m_buffer.size()) is_full = true;
    write_pos = (write_pos + len) % m_buffer.size();
}
void Buffer::ensure_writable(size_t len)
{
    if(writable_bytes() < len) 
    {
        if(is_full) 
        {
            size_t readable = readable_bytes();
            std::string str(peek(), write_pos);
            std::copy(begin_ptr() + read_pos, begin_ptr() + m_buffer.size(), begin_ptr());
            std::copy(str.data(), str.data() + str.size(), begin_ptr() + m_buffer.size() - read_pos);
            read_pos = 0;
            write_pos = read_pos + readable;
            is_full = false;
            assert(readable_bytes() == readable);
        }
        m_buffer.resize(write_pos + len + 1);
    }
    assert(writable_bytes() >= len);
}

void Buffer::buffer_append(const char* str, size_t len)
{
    assert(str);
    ensure_writable(len);
    size_t writable = m_buffer.size() - write_pos;
    if(!is_full && len > writable) 
    {
        std::copy(str, str + writable, begin_write());
        std::copy(str + writable + 1, str + len, begin_ptr());
    }
    else std::copy(str, str + len, begin_write());
    has_written(len);
}

void Buffer::append(const Buffer& buff)
{
    buffer_append(buff.peek(), buff.readable_bytes());
}

void Buffer::append(const std::string& str)
{
    buffer_append(str.data(), str.length());
}

void Buffer::append(const void* data, size_t len)
{
    assert(data);
    buffer_append(static_cast<const char*>(data), len);
}

ssize_t Buffer::read_fd(int fd, int* save_errno)
{
    char buff[65535];
    struct iovec iov[3];
    const size_t writable = writable_bytes();
    if(is_full)
    {
        iov[0].iov_base = begin_ptr() + write_pos;
        iov[0].iov_len =  writable;
        iov[1].iov_base = buff;
        iov[1].iov_len = sizeof(buff);
        iov[2].iov_base = nullptr;
        iov[2].iov_len = 0;
    }
    else
    {
        iov[0].iov_base = begin_ptr() + write_pos;
        iov[0].iov_len = m_buffer.size() - write_pos;
        iov[1].iov_base = begin_ptr();
        iov[1].iov_len = read_pos;
        iov[2].iov_base = buff;
        iov[2].iov_len = sizeof(buff);
    }
    ssize_t len = readv(fd, iov, 3);
    if(len < 0) *save_errno = errno;
    else if(static_cast<size_t>(len) <= writable)
    {
        if(write_pos + len >= m_buffer.size()) is_full = true;
        write_pos = (write_pos + len) % m_buffer.size();
    }
    else 
    {
        is_full = true;
        write_pos = (write_pos + writable) % m_buffer.size();
        buffer_append(buff, len - writable);
    }
    return len;
}

ssize_t Buffer::write_fd(int fd, int* save_errno)
{
    size_t readable = readable_bytes();
    ssize_t len = -1;
    if(is_full)
    {
        struct iovec iov[2];
        iov[0].iov_base = begin_ptr() + read_pos;
        iov[0].iov_len = m_buffer.size() - read_pos;
        iov[1].iov_base = begin_ptr();
        iov[1].iov_len = write_pos;
        len = writev(fd, iov, 2);   
    }
    else len = write(fd, peek(), readable);
    if(len < 0) *save_errno = errno;
    if(read_pos + len >= m_buffer.size()) is_full = false;
    read_pos = (read_pos + len) % m_buffer.size();
}