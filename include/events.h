#include <iomanip>
#include <memory>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#ifndef EVENT_H
#define EVENT_H

using std::queue;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::vector;
class EventListener;

#define MARKET_EVENT 0
#define QUIT_EVENT 1
#define SIGNAL_EVENT 2
#define ORDER_EVENT 3
#define EXECUTION_EVENT 4

class MarketEvent;
class SignalEvent;
class OrderEvent;
class ExecutionEvent;
class QuitEvent;

using EventVariant = std::variant<MarketEvent, QuitEvent>;

class Event {
public:
  string m_name;

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
  virtual void dispatch(const EventVariant event) = 0;
};

class EventListener {
public:
  string m_name;
  EventListener(string name) { m_name = name; }
  ~EventListener() {}
  virtual void onEvent(const EventVariant event) = 0;
};

class EventQueue {
private:
  std::queue<EventVariant> m_queue;
  std::mutex m_mutex;

public:
  EventQueue();
  ~EventQueue();

  void push(EventVariant &event);
  const size_t size();
  const EventVariant pop();
};

class QuitEvent : public Event {
public:
  QuitEvent() : Event("QUIT_EVENT") {}
};

class MarketEvent : public Event {
private:
  float m_open;
  float m_high;
  float m_low;
  float m_volume;

public:
  MarketEvent(float open, float high, float low, float vol)
      : m_open(open), m_high(high), m_low(low), m_volume(vol),
        Event("MARKET_EVENT") {}

  string toString() {
    std::stringstream stream;
    stream << " MarketEvent { open: " << std::fixed << std::setprecision(2)
           << m_open << " high: " << m_high << " low: " << m_low
           << " volume: " << m_volume << " }";

    return stream.str();
  }

  string toString() const {
    std::stringstream stream;
    stream << " MarketEvent { open: " << std::fixed << std::setprecision(2)
           << m_open << " high: " << m_high << " low: " << m_low
           << " volume: " << m_volume << " }";

    return stream.str();
  }
};

extern EventQueue event_queue;

#endif