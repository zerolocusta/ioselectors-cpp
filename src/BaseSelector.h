#ifndef BASESELECTOR_SRC_BASESELECTOR_H
#define BASESELECTOR_SRC_BASESELECTOR_H

#include <errno.h>

#include <map>
#include <vector>
#include <functional>
#include "boost/core/noncopyable.hpp"

namespace selector
{
class BaseSelector;
}

namespace selector
{

typedef std::function<void(int)> callback_func_t;
typedef std::map<int, callback_func_t> CallbackMap_t;

enum
{
  EVENT_READ = 1 << 0,
  EVENT_WRITE = 1 << 1
};

class BaseSelector : private boost::noncopyable
{

public:
  virtual ~BaseSelector() = default;

public:
  virtual void addEvent(int fd, int mask, const callback_func_t &callback) = 0;
  virtual void removeEvent(int fd) = 0;
  virtual void modifyEvent(int fd, int event_mask) = 0;
  virtual void modifyEvent(int fd, int event_mask, const callback_func_t &callback) = 0;
  virtual void loop(int timeoutMs) = 0;
};
}

#endif // BASESELECTOR_SRC_BASESELECTOR_H