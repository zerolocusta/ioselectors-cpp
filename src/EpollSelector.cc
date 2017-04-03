#include "EpollSelector.h"
#include <strings.h>
namespace selector
{


EpollSelector::EpollSelector()
    : epoll_fd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(InitEventListSize)
{
}

EpollSelector::~EpollSelector()
{

}

void EpollSelector::add_event(int fd, int event_mask, const callback_func_t &callback)
{
    struct epoll_event epoll_ev;
    bzero(&epoll_ev, sizeof(epoll_ev));
    epoll_ev.events = event_mask;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &epoll_ev);
    callbacks_[fd] = callback;
}

void EpollSelector::remove_event(int fd)
{
    auto it = callbacks_.find(fd);
    if (it != callbacks_.end())
        callbacks_.erase(it);
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
}

void EpollSelector::modify_event(int fd, int event_mask, const callback_func_t &callback)
{
    modify_event(fd, event_mask);
}

void EpollSelector::modify_event(int fd, int event_mask)
{
    struct epoll_event epoll_ev;
    bzero(&epoll_ev, sizeof(epoll_ev));
    epoll_ev.events = event_mask;
    epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &epoll_ev);
}

void EpollSelector::loop(int timeoutMs)
{

}

}


