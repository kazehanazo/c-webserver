#include "httprequest.h"

const std::unordered_set<std::string> HttpRequest::default_html
{
    "/index", "/login", "/register", "/welcome", "/video", "/picture",
};
const std::unordered_map<std::string, int> HttpRequest::default_html_tag
{
    {"/register.html", 0}, {"/login.html", 1},
};
void HttpRequest::init()
{
    m_method = m_path = m_version = m_body = "";
    m_state = REQUEST_LINE;
    m_header.clear();
    m_post.clear();
}
bool HttpRequest::is_keep_alive() const
{
    if(m_header.count("Connection") == 1)
    {
        return m_header.find("Connection")->second == "keep-alive" &&  m_version == "1.1";
    }
    else return false;
}
bool HttpRequest::parse(Buffer& buff)
{
    const char CRLF[] = "\r\n";
    if(buff.readable_bytes() <= 0) return false;
    while (buff.readable_bytes() && m_state != FINISH)
    {
        const char *line_end = std::search(buff.peek(), buff.begin_write_const(), CRLF, CRLF + 2);
        std::string line(buff.peek(), line_end);
        switch (m_state)
        {
        case REQUEST_LINE:
            if(!parse_request_line(line)) return false;
            parse_path();
            break;
        case HEADERS:
            parse_header(line);
            if(buff.readable_bytes() <= 2) m_state = FINISH;
            break;
        case BODY:
            std::cout <<  "BODY: " << line << std::endl;
            parse_body(line);
            break;
        default:
            break;
        }
        if(line_end == buff.begin_write()) break;
        buff.retrieve_until(line_end + 2);
    }
    LOG_DEBUG("[%s], [%s], [%s]", m_method.c_str(), m_path.c_str(), m_version.c_str());
    return true;
}
std::string HttpRequest::path() const
{
    return m_path;
}
std::string& HttpRequest::path()
{
    return m_path;
}
std::string HttpRequest::method() const
{
    return m_method;
}
std::string HttpRequest::version() const
{
    return m_version;
}
std::string HttpRequest::get_post(const std::string& key) const
{
    assert(key != "");
    if(m_post.count(key) == 1)
    {
        return m_post.find(key)->second;
    }
    return "";
}
std::string HttpRequest::get_post(const char* key) const
{
    assert(key != nullptr);
    if(m_post.count(key) == 1)
    {
        return m_post.find(key)->second;
    }
    return "";
}
int HttpRequest::converhex(char ch)
{
    if(ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if(ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return ch;
}
bool HttpRequest::parse_request_line(const std::string& line)
{
    std::regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch submatch;
    if(std::regex_match(line, submatch, patten))
    {
        m_method = submatch[1];
        m_path = submatch[2];
        m_version = submatch[3];
        m_state = HEADERS;
        return true;
    }
    LOG_ERROR("requestline matches error!");
    return false;
}
void HttpRequest::parse_header(const std::string& line)
{
    std::regex patten("^([^:]*): ?(.*)$");
    std::smatch submatch;
    if(std::regex_match(line, submatch, patten)) m_header[submatch[1]] = submatch[2];
    else m_state = BODY;
}
bool HttpRequest::parse_body(const std::string& line)
{
    m_body = line;
    parse_post();
    LOG_DEBUG("request 's body:%s, len:%d",line.c_str(),line.size());
}
void HttpRequest::parse_path()
{
    if(m_path == "/")
    {
        m_path = "/index.html";
    }
    else
    {
        for(auto &item: default_html)
        {
            if(m_path == item)
            {
                m_path = item + ".html";
                break;
            }
        }
    }
}
void HttpRequest::parse_from_urlencoded()
{
    if(m_body.size() == 0) return;
    std::string key,value;
    int num = 0;
    int i = 0,j = 0;
    for(;i < m_body.size();i++)
    {
        char ch = m_body[i];
        switch (ch)
        {
        case '=':
            key = m_body.substr(j, i - j);
            j = i + 1;
            break;
        case '+':
            m_body[i] = ' ';
            break;
        case '%':
            num = converhex(m_body[i + 1]) * 16 + converhex(m_body[i + 2]);
            m_body[i + 2] = num % 10 + '0';
            m_body[i + 1] = num / 10 + '0';
            i += 2;
            break;
        case '&':
            value = m_body.substr(j, i - j);
            j = i + 1;
            m_post[key] = value;
            LOG_DEBUG("post 's key:%s = value:%s", key.c_str(), value.c_str());
            break;
        default:
            break;
        }
    }
    assert(j <= i);
    if(m_post.count(key) == 0 && j < i)
    {
        value = m_body.substr(j, i -j);
        printf("value2: %s\n",value.c_str());
        m_post[key] = value;
        std::cout << m_post[key] << std::endl;
        LOG_DEBUG("post 's key:%s = value:%s", key.c_str(), value.c_str());
    }
}
void HttpRequest::parse_post()
{
    if(m_method == "POST" && m_header["Content-Type"] == "application/x-www-form-urlencoded")
    {
        parse_from_urlencoded();
        if(default_html_tag.count(m_path))
        {
            int tag = default_html_tag.find(m_path)->second;
            LOG_DEBUG("the post tag is %d", tag);
            if(tag == 0 || tag == 1)
            {
                bool is_login = (tag == 1);
                if(user_verify(m_post["username"], m_post["password"], is_login)) m_path = "/welcome.html";
                else m_path = "/error.html";
            }
        }
    }
}
bool HttpRequest::user_verify(const std::string &name, const std::string &pwd, bool is_login)
{
    if(name == "" || pwd == "") return false;
    LOG_INFO("verify name: %s pwd: %s",name.c_str(), pwd.c_str());
    MYSQL *sql;
    SqlConnRAII(&sql, SqlConnPool::get_instance());
    assert(sql);
    unsigned int j = 0;
    char order[256] = { 0 };
    bool flag = false;
    MYSQL_FIELD *fields = nullptr;
    MYSQL_RES *res = nullptr;
    if(!is_login) flag = true;
    snprintf(order, 256, "SELECT username, password FROM user WHERE username =  '%s' LIMIT 1", name.c_str());
    LOG_DEBUG("%s", order);
    if(mysql_query(sql, order))
    {
        mysql_free_result(res);
        return false;
    }
    res = mysql_store_result(sql);
    j = mysql_num_fields(res);
    fields = mysql_fetch_fields(res);
    while (MYSQL_ROW row = mysql_fetch_row(res))
    {
        LOG_DEBUG("mysql row username:%s password:%s",row[0], row[1]);
        std::string password = row[1];
        if(is_login)
        {
            if(pwd == password) flag = true;
            else 
            {
                flag = false;
                LOG_DEBUG("the password is error!");
            }
        }
        else
        {
            flag = false;
            LOG_DEBUG("the username is existed!");
        }
    }
    mysql_free_result(res);
    if(!is_login && flag == true)
    {
        LOG_DEBUG("user regirster");
        bzero(order, 256);
        snprintf(order, 256, "INSERT INTO user(username, password) VALUES ('%s', '%s')", name.c_str(),pwd.c_str());
        LOG_DEBUG("%s", order);
        if(mysql_query(sql, order))
        {
            LOG_DEBUG("insert user error!");
            flag =  false;
        }
        flag = true;
    }
    SqlConnPool::get_instance()->release_conn(sql);
    LOG_DEBUG("user verify is successed!");
    return flag;
}
