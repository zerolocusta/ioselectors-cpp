#ifndef SELECTOR_SRC_EPOLLSELECTOR_H
#define SELECTOR_SRC_EPOLLSELECTOR_H

#include "BaseSelector.h"

#include <errno.h>
#include <poll.h>
#include <sys/epoll.h>

#include <map>
#include <vector>
#include <functional>
#include <exception>
#include "boost/core/noncopyable.hpp"

namespace selector
{

class EBADFexception : public std::exception
{
  const char *what() const throw()
  {
    return "[EBADF] epoll_fd or fd is not a valid file descriptor";
  }
};

class EEXITexception : public std::exception
{
  const char *what() const throw()
  {
    return "[EEXIT] op  was  EPOLL_CTL_ADD,"
           "and the supplied file descriptor fd "
           "is already registered with this epoll instance.";
  }
};

class EINVALexception : public std::exception
{
  const char *what() const throw()
  {
    return "[EINVAL] epfd is not an epoll file descriptor, "
           "or fd is the same  as epfd, "
           "or  the  requested  operation op is not supported by "
           "this interface.";
  }
};

class ENOENTexception : public std::exception
{
  const char *what() const throw()
  {
    return "[ENOENT]op was EPOLL_CTL_MOD or EPOLL_CTL_DEL,"
           " and fd is not registered with this epoll instance.";
  }
};

class ENOMEMexception : public std::exception
{
  const char *what() const throw()
  {
    return "[ENOMEM] There  was  insufficient  memory to "
           "handle the requested op"
           "control operation.";
  }
};

class ENOSPCexception : public std::exception
{
  const char *what() const throw()
  {
    return "[ENOSPC]The limit  imposed  by  /proc/sys/fs/epoll/max_user_watches"
           "was  encountered while trying to register (EPOLL_CTL_ADD) a"
           "new file descriptor on an epoll instance.  See epoll(7) for"
           "further details.";
  }
};

class EPERMexception : public std::exception
{
  const char *what() const throw()
  {
    return "[EPERM] The  target file fd does not support epoll.  This error can "
           "occur if fd refers to, for example, a  regular  file  or  a"
           "directory.";
  }
};

class EpollSelector : public BaseSelector
{
  typedef std::vector<struct epoll_event> EventList_t;

public:
  EpollSelector();
  ~EpollSelector();

  void add_event(int fd, int mask, const callback_func_t &callback) override;
  void remove_event(int fd) override;
  void modify_event(int fd, int event_mask) override;
  void modify_event(int fd, int event_mask, const callback_func_t &callback) override;
  void loop(int timeoutMs) override;

private:
  void update_event(int fd, int mask, const callback_func_t &callback);

private:
  static const int InitEventListSize = 16;
  int epoll_fd_;
  EventList_t events_;
  CallbackMap_t callbacks_;
};
}

#endif // PRACTICE_SRC_EPOLLSELECTOR_H