#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "events.h"
#include <vector>

using std::vector;

class DataHandler : public EventDispatcher {
private:
  vector<Event> m_events;

public:
  DataHandler();
  ~DataHandler();

  virtual void addListener(shared_ptr<EventListener> listener) = 0;
  virtual void removeListener(shared_ptr<EventListener> listener) = 0;
  virtual void dispatch(const Event &event) = 0;
};

#endif