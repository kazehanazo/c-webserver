#include <unistd.h>
#include "src/server/webserver.h"
#include "src/config/config.h"

int main(int argc, char *argv[])
{
    Config config;
    config.parse_arg(argc, argv);
    WebServer webserver(config.port, config.sql_port, config.sql_user, config.sql_pwd,
                                                    config.db_name, config.connpool_num, config.thread_num, config.open_log,
                                                    config.log_quesize, config.trig_mode, config.timeout_ms, config.opt_linger);
    webserver.start();
}