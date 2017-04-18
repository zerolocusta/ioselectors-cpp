#ifndef DEFAULTSELECTOR_SRC_SELECTOR_H
#define DEFAULTSELECTOR_SRC_SELECTOR_H
#include <errno.h>

#include <map>
#include <vector>
#include <functional>
#include "boost/noncopyable.hpp"

#include "BaseSelector.h"

namespace selector
{
class DefaultSelector : public BaseSelector
{

  typedef std::vector<int> EventList_t;

public:
  DefaultSelector();
  ~DefaultSelector();

  void addEvent(int fd, int event_mask, const callback_func_t &callback) override;
  void removeEvent(int fd) override;
  void modifyEvent(int fd, int event_mask) override;
  void modifyEvent(int fd, int event_mask, const callback_func_t &callback) override;
  void loop(int timeoutMs) override;

private:
  void updateEvent(int fd, int mask, const callback_func_t &callback);

private:
  int epoll_fd_;
  EventList_t events_;
  CallbackMap_t callbacks_;
};
}

#endif // DEFAULTSELECTOR_SRC_SELECTOR_H