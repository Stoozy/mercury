#include <memory>
#include <string>
#include <vector>

#ifndef EVENT_H
#define EVENT_H

using std::shared_ptr;
using std::string;
using std::vector;
class EventListener;

typedef enum event_type {
  MARKET_EVENT,
  SIGNAL_EVENT,
  ORDER_EVENT,
  EXECUTION_EVENT
} EventType;

class Event {
private:
  string m_name;

public:
  virtual ~Event() {}
  virtual string getName() { return m_name; }
};

class EventDispatcher {
public:
  vector<shared_ptr<EventListener>> m_listeners;
  EventDispatcher() {}
  virtual ~EventDispatcher() {}

  virtual void addListener(shared_ptr<EventListener> listener) = 0;
  virtual void removeListener(shared_ptr<EventListener> listener) = 0;
  virtual void dispatch(const Event &event) = 0;
};

class EventListener {
public:
  string m_name;
  EventListener(string name) { m_name = name; }
  ~EventListener() {}
  virtual void onEvent(const Event &event) = 0;
};

#endif