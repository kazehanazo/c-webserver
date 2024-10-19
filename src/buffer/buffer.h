#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <cstring> 
#include <atomic>
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/uio.h>

class Buffer
{
private:
    std::vector<char> m_buffer;
    std::atomic<std::size_t> read_pos;
    std::atomic<std::size_t> write_pos;
    std::atomic<std::size_t> m_size;
    bool is_full;
    char* begin_ptr();
    const char* begin_ptr() const;

public:
    Buffer(int buff_size = 2048);
    size_t readable_bytes() const;
    size_t writable_bytes() const;
    size_t prependable_bytes() const;
    const char* peek() const;
    void retrieve(size_t len);
    void retrieve_until(const char* end);
    void retrieve_all();
    std::string retrieve_to_str();
    const char* begin_write_const() const;
    char* begin_write();
    void has_written(size_t len);
    void ensure_writable(size_t len);
    void buffer_append(const char* str, size_t len);
    void append(const Buffer& buff);
    void append(const std::string& str);
    void append(const void* data, size_t len);
    ssize_t read_fd(int fd, int* save_errno);
    ssize_t write_fd(int fd, int* save_errno);
    ~Buffer() = default;
};

#endif