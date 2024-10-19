#include "httpresponse.h"

const std::unordered_map<std::string, std::string> HttpResponse::SUFFIX_TYPE = {
    { ".html",  "text/html" },
    { ".xml",   "text/xml" },
    { ".xhtml", "application/xhtml+xml" },
    { ".txt",   "text/plain" },
    { ".rtf",   "application/rtf" },
    { ".pdf",   "application/pdf" },
    { ".word",  "application/nsword" },
    { ".png",   "image/png" },
    { ".gif",   "image/gif" },
    { ".jpg",   "image/jpeg" },
    { ".jpeg",  "image/jpeg" },
    { ".au",    "audio/basic" },
    { ".mpeg",  "video/mpeg" },
    { ".mpg",   "video/mpeg" },
    { ".avi",   "video/x-msvideo" },
    { ".gz",    "application/x-gzip" },
    { ".tar",   "application/x-tar" },
    { ".css",   "text/css "},
    { ".js",    "text/javascript "},
};

const std::unordered_map<int, std::string> HttpResponse::CODE_STATUS = {
    { 200, "OK" },
    { 400, "Bad Request" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
};

const std::unordered_map<int, std::string> HttpResponse::CODE_PATH = {
    { 400, "/400.html" },
    { 403, "/403.html" },
    { 404, "/404.html" },
};

HttpResponse::HttpResponse()
{
    m_dir = m_path = "";
    m_is_keep_alive = false;
    m_code = -1;
    m_mmfile = nullptr;
    m_mmfile_stat = { 0 };
}

void HttpResponse::init(const std::string &dir, std::string path, bool is_keep_alive, int code)
{
    assert(dir != "");
    if(m_mmfile) umap_file(); 
    m_dir = dir;
    m_path = path;
    m_is_keep_alive = is_keep_alive;
    m_code = code;
    m_mmfile = nullptr;
    m_mmfile_stat = { 0 };
}

void HttpResponse::do_response(Buffer &buff)
{
    if(stat((m_dir + m_path).data(), &m_mmfile_stat ) < 0 || S_ISDIR(m_mmfile_stat.st_mode)) m_code = 404;
    else if(!(m_mmfile_stat.st_mode & S_IROTH)) m_code = 403;
    else if(m_code == -1) m_code = 200;
    error_html();
    add_status_line(buff);
    add_header(buff);
    add_content(buff);
}

char* HttpResponse::file()
{
    return m_mmfile;
}

size_t HttpResponse::flie_len()const
{
    return m_mmfile_stat.st_size;
}

void HttpResponse::umap_file()
{
    if(m_mmfile)
    {
        munmap(m_mmfile, m_mmfile_stat.st_size);
        m_mmfile = nullptr;
    }
}

void HttpResponse::error_content(Buffer &buff, std::string message)
{
    std::string body;
    std::string status;
    body += "<html><title>Error</title>";
    body += "<body bgcolor=\"ffffff\">";
    if(CODE_STATUS.count(m_code) == 1) status = CODE_STATUS.find(m_code)->second;
    else status = "Bad Request";
    body += std::to_string(m_code) + " : " + status  + "\n"; 
    body += "<p>" + message + "</p>";  
    body += "<hr><em>TinyWebServer</em></body></html>"; 
    buff.append("Content-length: " + std::to_string(body.size()) + "\r\n\r\n");
    buff.append(body);
}

void HttpResponse::error_html()
{
    if(CODE_PATH.count(m_code) == 1)
    {
        m_path = CODE_PATH.find(m_code)->second;
        stat((m_dir + m_path).data(), &m_mmfile_stat);
    }
}

std::string HttpResponse::get_file_type()
{
    std::string::size_type idx = m_path.find_last_of('.');
    if(idx == std::string::npos) return "text/plain";
    std::string suffix = m_path.substr(idx);
    if(SUFFIX_TYPE.count(suffix) == 1) return SUFFIX_TYPE.find(suffix)->second;
    return "text/plain";
}
// bool HttpResponse::add_response_line(const char* format, ...)
// {
//     if(m_write_idx >= WRITE_BUFFER_SIZE) return false;
//     va_list format_list;
//     va_start(format_list, format);
//     int len = vsnprintf(m_write_buff + m_write_idx, WRITE_BUFFER_SIZE - m_write_idx - 1, format, format_list);
//     if(len >= (WRITE_BUFFER_SIZE - m_write_idx - 1))
//     {
//         va_end(format_list);
//         return false;
//     }
//     m_write_idx += len;
//     va_end(format_list);
//     LOG_DEBUG("write response: %s", m_write_buff);
//     return true;
// }
void HttpResponse::add_status_line(Buffer &buff)
{
    std::string status;
    if(CODE_STATUS.count(m_code) == 1)
    {
        status = CODE_STATUS.find(m_code)->second;
    }
    else
    {
        m_code = 400;
        status = CODE_STATUS.find(m_code)->second;
    }
    buff.append("HTTP/1.1 " + std::to_string(m_code) + " " + status + "\r\n");
}

void HttpResponse::add_header(Buffer &buff)
{
    buff.append("Connection: ");
    if(m_is_keep_alive)
    {
        buff.append("keep-alive\r\n");
        buff.append("keep-alive: max=6, timeout=120\r\n");
    }
    else buff.append("close\r\n");
    buff.append("Content-type: " + get_file_type() + "\r\n");
}

void HttpResponse::add_content(Buffer &buff)
{
    int src_fd = open((m_dir + m_path).data(), O_RDONLY);
    if(src_fd < 0)
    {
        error_content(buff, "file path is not found !");
        return;
    }
    LOG_DEBUG("open file path: %s", (m_dir + m_path).data());
    int* mm_ret = (int *)mmap(0, m_mmfile_stat.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if(*mm_ret == -1)
    {
        error_content(buff, "file mapping is not found !");
        return;
    }
    m_mmfile = (char *)mm_ret;
    close(src_fd);
    buff.append("Content-length: " + std::to_string(m_mmfile_stat.st_size) + "\r\n\r\n");
}
HttpResponse::~HttpResponse()
{
    umap_file();
}