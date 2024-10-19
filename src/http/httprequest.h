#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <regex>
#include <error.h>
#include <mysql/mysql.h>

#include "../log/log.h"
#include "../buffer/buffer.h"
#include "../pool/sqlconnpool.h"
#include "../pool/sqlconnRAII.h"

class HttpRequest
{
public:
    // 枚举解析状态
    enum PARSE_STATE {
        REQUEST_LINE,  // 解析请求行
        HEADERS,       // 解析请求头
        BODY,          // 解析请求体
        FINISH,        // 完成解析
    };
    // 枚举 HTTP 状态码
    enum HTTP_CODE {
        NO_REQUEST = 0,     // 无请求
        GET_REQUEST,        // GET 请求
        BAD_REQUEST,        // 错误请求
        NO_RESOURSE,        // 无资源
        FORBIDDENT_REQUEST, // 禁止请求
        FILE_REQUEST,       // 文件请求
        INTERNAL_ERROR,     // 服务器内部错误
        CLOSED_CONNECTION,  // 连接关闭
    };

    HttpRequest() { init(); }
    void init();
    bool is_keep_alive() const;
    bool parse(Buffer& buff);
    std::string path() const;
    std::string& path();
    std::string method() const;
    std::string version() const;
    std::string get_post(const std::string& key) const;
    std::string get_post(const char* key) const;
    ~HttpRequest() = default;
private:
    PARSE_STATE m_state;
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::string m_body;
    std::unordered_map<std::string, std::string> m_header;
    std::unordered_map<std::string, std::string> m_post;
    static const std::unordered_set<std::string> default_html;
    static const std::unordered_map<std::string, int> default_html_tag;
    static int converhex(char ch);

    bool parse_request_line(const std::string& line);
    void parse_header(const std::string& line);
    bool parse_body(const std::string& line);  
    void parse_path();
    void parse_post();
    void parse_from_urlencoded();
    static bool user_verify(const std::string &name, const std::string &pwd, bool is_login);
};

#endif