#include "EpollSelector.h"
#include <strings.h>
#include <unistd.h>
namespace selector
{

EpollException::EpollException(int epoll_errno)
    : epoll_errno_(epoll_errno)
{
}

const char *EpollException::what() const throw()
{
    switch (epoll_errno_)
    {
    case EBADF:
        return "[EBADF] epoll_fd or fd is not a valid file descriptor";
        break;
    case EEXIST:
        return "[EEXIST] op  was  EPOLL_CTL_ADD,"
               "and the supplied file descriptor fd "
               "is already registered with this epoll instance.";
        break;
    case EINVAL:
        return "[EINVAL] epfd is not an epoll file descriptor, "
               "or fd is the same  as epfd, "
               "or  the  requested  operation op is not supported by "
               "this interface.";
    case ENOENT:
        return "[ENOENT]op was EPOLL_CTL_MOD or EPOLL_CTL_DEL,"
               " and fd is not registered with this epoll instance.";
        break;
    case ENOMEM:
        return "[ENOMEM] There  was  insufficient  memory to "
               "handle the requested op"
               "control operation";
        break;
    case ENOSPC:
        return "[ENOSPC]The limit  imposed  by  /proc/sys/fs/epoll/max_user_watches"
               "was  encountered while trying to register (EPOLL_CTL_ADD) a"
               "new file descriptor on an epoll instance.  See epoll(7) for"
               "further details.";
        break;
    case EPERM:
        return "[EPERM] The  target file fd does not support epoll.  This error can "
               "occur if fd refers to, for example, a  regular  file  or  a"
               "directory.";
        break;
    default:
        return "[UNKNOWN ERROR] unknown epoll error";
        break;
    }
}

const int EpollException::getErrno() const
{
    return epoll_errno_;
}

EpollSelector::EpollSelector()
    : epoll_fd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(InitEventListSize)
{
}

EpollSelector::~EpollSelector()
{
    close(epoll_fd_);
}

int EpollSelector::eventMaskToEpollMask(int event_mask)
{
    int mask = 0;
    if (event_mask & EVENT_READ)
        mask |= EPOLLIN;
    if (event_mask & EVENT_WRITE)
        mask |= EPOLLOUT;
    return mask;
}

void EpollSelector::updateEvent(int fd, int operation, int event_mask)
{
    int ret = 0;
    if (operation == EPOLL_CTL_DEL)
        ret = epoll_ctl(epoll_fd_, operation, fd, NULL);
    else
    {
        struct epoll_event epoll_ev;
        bzero(&epoll_ev, sizeof(epoll_ev));
        int epoll_mask = eventMaskToEpollMask(event_mask);
        epoll_ev.events = epoll_mask;
        ret = epoll_ctl(epoll_fd_, operation, fd, &epoll_ev);
    }
    if (ret < 0)
        throw EpollException(errno);
}

void EpollSelector::addEvent(int fd, int event_mask, const callback_func_t &callback)
{
    updateEvent(fd, EPOLL_CTL_ADD, event_mask);
    callbacks_[fd] = callback;
}

void EpollSelector::removeEvent(int fd)
{
    auto it = callbacks_.find(fd);
    if (it != callbacks_.end())
        callbacks_.erase(it);
    updateEvent(fd, EPOLL_CTL_DEL, 0);
}

void EpollSelector::modifyEvent(int fd, int event_mask, const callback_func_t &callback)
{
    modifyEvent(fd, event_mask);
    callbacks_[fd] = callback;
}

void EpollSelector::modifyEvent(int fd, int event_mask)
{
    updateEvent(fd, EPOLL_CTL_MOD, event_mask);
}

void EpollSelector::loop(int timeoutMs)
{
}
}
