#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "events.h"
#include <vector>

using std::vector;

class DataHandler : EventDispatcher {
public:
  DataHandler();
  ~DataHandler();

  // @brief Listens to alternate thread (market simulation)
  // and dispatches new events to listeners
  void run();

  void addListener(shared_ptr<EventListener> listener);
  void removeListener(shared_ptr<EventListener> listener);
  void dispatch(const Event &event);
};

#endif