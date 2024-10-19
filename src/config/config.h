#ifndef CONFIG_H
#define CONFIG_H

#include "../server/webserver.h"

class Config
{
public:
    int port;
    int sql_port;
    const char* sql_user;
    const char* sql_pwd;
    const char* db_name;
    int connpool_num;
    int thread_num;
    bool open_log;
    int log_quesize;
    int trig_mode;
    int timeout_ms;
    bool opt_linger;
    Config();
    void parse_arg(int argc, char*argv[]);
    ~Config() = default;
};




#endif