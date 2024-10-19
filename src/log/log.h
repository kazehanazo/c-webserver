#ifndef LOG_H
#define LOG_H

#include <string>
#include <mutex>
#include <thread>
#include <iostream>
#include <string.h>
#include <stdarg.h> 
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

#include "blockqueue.h"
#include "../buffer/buffer.h"
class Log
{
private:
    static const int log_file_len = 256;
    static const int max_log_rows = 50000;
    const char* log_path;
    const char* log_name;
    FILE *m_fp;
    //Buffer m_buff;
    char *m_buff;
    int m_log_buff_size;
    int m_log_rows;
    int m_today;
    std::mutex m_mutex;
    std::unique_ptr<BlockQueue<std::string>>  m_log_queue; 
    std::unique_ptr<std::thread> m_write_Thread;
    bool is_async;
    bool m_open;
private:
    Log();
    void async_write();
    virtual ~Log();
public:
    static Log *get_instance()
    {
        static Log instance;
        return &instance;
    }
    //int log_buff_size = 8192, int log_rows = 5000000, 
    void init(const char *path, const char *name, int max_queue_size = 0);
    void write_log(int level, const char *format, ...);
    static void flush_log_thread();
    void flush();
    bool is_open() { return m_open; }
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    Log(const Log&&) = delete;
    Log& operator=(const Log&&) = delete;
};
#define LOG_BASE(level, format, ...) \
    do { \
        Log* log = Log::get_instance();\
        if(log->is_open()) { \
            log->write_log(level, format, ##__VA_ARGS__); \
            log->flush(); \
        } \
    } while(0);
#define LOG_DEBUG(format, ...) do {LOG_BASE(0, format, ##__VA_ARGS__)} while(0);
#define LOG_INFO(format, ...) do {LOG_BASE(1, format, ##__VA_ARGS__)} while(0);
#define LOG_WARN(format, ...) do {LOG_BASE(2, format, ##__VA_ARGS__)} while(0);
#define LOG_ERROR(format, ...) do {LOG_BASE(3, format, ##__VA_ARGS__)} while(0);

#endif