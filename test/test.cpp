#include "../log/log.h"
#include "../pool/threadpool.h"
#include <features.h>
#include <unistd.h>  

#define PATH "./log_data"
#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

void TestLog() {
    int cnt = 0, level = 0;
    Log::get_instance()->init(PATH, "test.log", 50000);
    for(int j = 0; j < 10000; j++ ){
        for(int i = 0; i < 4; i++) {
            LOG_INFO("%s 111111111 %d ============= ", "Test", cnt++);
        }
    }

}

void ThreadLogTask(int i, int cnt) {
    for(int j = 0; j < 10000; j++ ){
        LOG_BASE(i,"PID:[%04d]======= %05d ========= ", gettid(), cnt++);
    }
}
void TestThreadPool()
{
    Log::get_instance()->init(PATH, "test_threadpool.log", 50000);
    ThreadPool threadpool(6);
    for(int i = 0;i < 18;i++)
    {
        threadpool.addTask(std::bind(ThreadLogTask, i % 4, i * 10000));
    }
    getchar();
}

int main()
{
    TestLog();
    //TestThreadPool();
}
