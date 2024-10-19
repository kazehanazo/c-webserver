#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <vector>

class Epoller
{
private:
    int m_epollfd;
    std::vector<struct epoll_event> m_events;
public:
    explicit Epoller(int max_events = 1024);
    bool add_fd(int fd, uint32_t events);
    bool mod_fd(int fd, uint32_t events);
    bool del_fd(int fd);
    int wait(int timeout = -1);
    int get_event_fd(size_t i) const;
    uint32_t get_epoll_events(size_t i) const;
    ~Epoller();
};

#endif