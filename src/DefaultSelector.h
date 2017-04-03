#ifndef DEFAULTSELECTOR_SRC_SELECTOR_H
#define DEFAULTSELECTOR_SRC_SELECTOR_H
#include <errno.h>

#include <map>
#include <vector>
#include <functional>
#include "boost/core/noncopyable.hpp"

#include "BaseSelector.h"

namespace selector
{
class DefaultSelector : public BaseSelector
{

  typedef std::vector<int> EventList_t;

public:
  DefaultSelector();
  ~DefaultSelector();

  void add_event(int fd, int mask, const callback_func_t &callback) override;
  void remove_event(int fd) override;
  void modify_event(int fd, int event_mask) override;
  void modify_event(int fd, int event_mask, const callback_func_t &callback) override;
  void loop(int timeoutMs) override;

private:
  void update_event(int fd, int mask, const callback_func_t &callback);

private:
  int epoll_fd_;
  EventList_t events_;
  CallbackMap_t callbacks_;
};
}

#endif // DEFAULTSELECTOR_SRC_SELECTOR_H