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

class EpollException : public std::exception
{
public:
  EpollException(int epoll_errno);
  const char *what() const throw();
  const int getErrno() const;

private:
  int epoll_errno_;
};

class EpollSelector : public BaseSelector
{
  typedef std::vector<struct epoll_event> EventList_t;

public:
  EpollSelector();
  ~EpollSelector();

  void addEvent(int fd, int mask, const callback_func_t &callback) override;
  void removeEvent(int fd) override;
  void modifyEvent(int fd, int event_mask) override;
  void modifyEvent(int fd, int event_mask, const callback_func_t &callback) override;
  void loop(int timeoutMs) override;

private:
  int eventMaskToEpollMask(int event_mask);
  int epollMaskToEventMask(int epoll_mask);
  void extendEventListSize();
  void updateEvent(int fd, int operation, int event_mask);

private:
  static const int InitEventListSize = 16;
  int epoll_fd_;
  EventList_t events_;
  CallbackMap_t callbacks_;
};
}

#endif // PRACTICE_SRC_EPOLLSELECTOR_H