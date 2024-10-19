#include "config.h"

Config::Config()
{
    timeout_ms = 50000;
    sql_port = 3306;
    sql_user = "root";
    sql_pwd = "123157";
    db_name = "user_info";

    port = 8080;
    connpool_num = 0;
    thread_num = 0;
    open_log = false;
    log_quesize = 0;
    trig_mode = 0;
    opt_linger = false;
}

void Config::parse_arg(int argc, char*argv[]){
    int opt;
    const char *str = "p:s:t:c:l:m:o:";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            port = atoi(optarg);
            break;
        }
        case 's':
        {
            connpool_num = atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num = atoi(optarg);
            break;
        }
        case 'c':
        {
            int num = atoi(optarg);
            if(num == 0) open_log = true;
            else open_log = false; 
            break;
        }
        case 'l':
        {
            log_quesize = atoi(optarg);
            break;
        }
        case 'm':
        {
            trig_mode = atoi(optarg);
            break;
        }
        case 'o':
        {
            int num = atoi(optarg);
            if(num == 1) opt_linger = true;
            else opt_linger = false; 
            break;
        }
        default:
            break;
        }
    }
}