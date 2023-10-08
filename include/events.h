#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

#ifndef EVENT_H
#define EVENT_H

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;
class EventListener;

typedef enum event_type {
  MARKET_EVENT,
  SIGNAL_EVENT,
  ORDER_EVENT,
  EXECUTION_EVENT,
  QUIT_EVENT
} EventType;

class Event {

public:
  string m_name;
  EventType type;

  Event(string name) : m_name(name) {}
  virtual ~Event() {}
  virtual string toString() { return m_name; }
  virtual string toString() const { return m_name; }
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

class EventQueue {
private:
  std::queue<Event> m_queue;
  std::mutex m_mutex;

public:
  EventQueue();
  ~EventQueue();

  void push(const Event &event);
  const size_t size();
  const Event pop();
};

extern EventQueue event_queue;

#endif