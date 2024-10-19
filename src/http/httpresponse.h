#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <unordered_map>
#include <cstdarg>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "../log/log.h"
#include "../buffer/buffer.h"

class HttpResponse
{
public:
    //static const int WRITE_BUFFER_SIZE = 1024;

    HttpResponse();
    void init(const std::string &dir, std::string path, bool is_keep_alive = false, int code = -1);
    void do_response(Buffer  &buff);
    char* file();
    size_t flie_len() const;
    void umap_file();
    void error_content(Buffer &buff, std::string message);
    int get_code() const { return m_code; }
    ~HttpResponse();

private:
    int m_code;
    bool m_is_keep_alive;
    std::string m_dir;
    std::string m_path;
    // char m_write_buff[WRITE_BUFFER_SIZE];
    // int m_write_idx;
    char* m_mmfile;
    struct  stat m_mmfile_stat;
    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
    static const std::unordered_map<int, std::string> CODE_STATUS;
    static const std::unordered_map<int, std::string> CODE_PATH;

    void error_html();
    std::string get_file_type();
    //bool add_response_line(const char* format, ...);
    void add_status_line(Buffer &buff);
    void add_header(Buffer &buff);
    void add_content(Buffer &buff);
};

#endif