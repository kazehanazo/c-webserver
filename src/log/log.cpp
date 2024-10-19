#include "log.h"

Log::Log()
{
    m_log_rows = 0;
    m_today = 0;
    m_fp = nullptr;
    is_async = false;
    m_log_queue = nullptr;
    m_write_Thread = nullptr;

}
void Log::async_write()
{
    std::string str = "";
    while(m_log_queue->pop(str))
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        fputs(str.c_str(), m_fp);
    }
}
void Log::flush_log_thread()
{
    Log::get_instance()->async_write();
}
void Log::flush()
{
    std::lock_guard<std::mutex> locker(m_mutex);
    if(is_async)
    {
        m_log_queue->flush();
    }
    fflush(m_fp);
}
void Log::init(const char *path, const char *name, int max_queue_size)
{
    if(max_queue_size> 0)
    {
        is_async = true;
        if(!m_log_queue)
        {
            std::unique_ptr<BlockQueue<std::string>> new_queue(new BlockQueue<std::string>);
            m_log_queue = move(new_queue);
            std::unique_ptr<std::thread> new_thread(new std::thread(flush_log_thread));
            m_write_Thread = move(new_thread);
        }
    }
    m_open = true;
    m_log_buff_size = 8192;
    m_buff = new char[m_log_buff_size];
    memset(m_buff, '\0', m_log_buff_size);
    m_log_rows = 0;
    time_t t = time(NULL);
    struct tm *sys_time = localtime(&t);
    struct tm m_time = *sys_time;
    m_today = m_time.tm_mday;
    log_path = path;
    log_name = name;
    char file_name[log_file_len] = {0};
    snprintf(file_name, log_file_len - 1, "%s/%04d_%02d_%02d_%s", 
                        log_path, m_time.tm_year + 1900, m_time.tm_mon + 1, m_time.tm_mday, log_name);
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if(m_fp)
        {
            flush();
            fclose(m_fp);
        }    
        m_fp = fopen(file_name, "a");
        if(m_fp == nullptr)
        {
            mkdir(log_path, 0777);
            m_fp = fopen(file_name, "a");
        }
        assert(m_fp != nullptr);
    }
}
void Log::write_log(int level, const char *format, ...)
{
    struct  timeval now = {0, 0};
    gettimeofday(&now, NULL);
    time_t t = now.tv_sec;
    struct tm *sys_time = localtime(&t);
    struct tm m_time = *sys_time;
    va_list format_list;
    char s[16] = {0};
    switch (level)
    {
    case 0:
        strcpy(s, "[debug]:");
        break;
    case 1:
        strcpy(s, "[info]:");
        break;
    case 2:
        strcpy(s, "[warn]:");
        break;
    case 3:
        strcpy(s, "[erro]:");
        break;
    default:
        strcpy(s, "[info]:");
        break;
    }
    m_log_rows++;
    if(m_today != m_time.tm_mday || (m_log_rows % max_log_rows) == 0)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        locker.unlock();
        char new_file[log_file_len];
        char tail[16] = {0};
        snprintf(tail, 16, "%04d_%02d_%02d", m_time.tm_year + 1900, m_time.tm_mon + 1, m_time.tm_mday);
        if(m_today != m_time.tm_mday)
        {
            snprintf(new_file, log_file_len - 1, "%s/%s_%s", log_path, tail, log_name);
            m_today = m_time.tm_mday;
            m_log_rows = 0;
        }
        else
        {
            snprintf(new_file, log_file_len - 1, "%s/%s_%d_%s", log_path, tail, m_log_rows / max_log_rows, log_name);
        }
        locker.lock();
        flush();
        fclose(m_fp);
        m_fp = fopen(new_file, "a");
        assert(m_fp != nullptr);
    }
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        int n = snprintf(m_buff, 48, "%04d-%02d-%02d %02d:%02d:%02d.%06ld %s",
                                            m_time.tm_year + 1900, m_time.tm_mon + 1, m_time.tm_mday,
                                            m_time.tm_hour, m_time.tm_min, m_time.tm_sec, now.tv_usec, s);   
        va_start(format_list, format);
        int m = vsnprintf(m_buff + n, log_file_len - n - 1,format, format_list);
        va_end(format_list);
        m_buff[n + m] = '\n';
        m_buff[n +m + 1] = '\0';
        std::string log_str = m_buff;
        if(is_async && m_log_queue && !m_log_queue->full())
        {
            m_log_queue->push_back(log_str);
        }
        else
        {
            fputs(log_str.c_str(), m_fp);
        }
    }
}
Log::~Log()
{
    if(m_write_Thread && m_write_Thread->joinable())
    {
        while(! m_log_queue->empty())
        {
            m_log_queue->flush();
        }
        m_log_queue->close();
        m_write_Thread->join();
    }
    if(m_fp)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        flush();
        fclose(m_fp);
    }
}