#include "epoller.h"

Epoller::Epoller(int max_events): m_epollfd(epoll_create(512)), m_events(max_events)
{
    assert(m_epollfd >= 0 && m_events.size() > 0);
}

bool Epoller::add_fd(int fd, uint32_t events)
{
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &ev) == 0;
}

bool Epoller::mod_fd(int fd, uint32_t events)
{
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &ev) == 0;
}

bool Epoller::del_fd(int fd)
{
    if(fd < 0) return false;
    epoll_event ev = {0};
    return epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, &ev) == 0;
}

int Epoller::wait(int timeout)
{
    return epoll_wait(m_epollfd, &m_events[0], static_cast<int>(m_events.size()), timeout);
}

int Epoller::get_event_fd(size_t i) const
{
    assert(i >= 0 && i < m_events.size());
    return m_events[i].data.fd;
}

uint32_t Epoller::get_epoll_events(size_t i) const
{
    assert(i >= 0 && i < m_events.size());
    return m_events[i].events;
}
Epoller::~Epoller()
{
    close(m_epollfd);
}