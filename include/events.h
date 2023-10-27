#include <ctime>
#include <iomanip>
#include <memory>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <types.h>
#ifndef EVENT_H
#define EVENT_H

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;
class EventListener;

#define QUIT_EVENT 0
#define MARKET_EVENT 1
#define SIGNAL_EVENT 2
#define ORDER_EVENT 3

class MarketEvent;
class SignalEvent;
class OrderEvent;
class QuitEvent;

using EventVariant =
    std::variant<QuitEvent, MarketEvent, SignalEvent, OrderEvent>;

class Event {
protected:
  string m_name;

  // TODO: keep timestamp here

public:
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
  size_t size();
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
  string m_symbol;

  MarketEvent(string symbol, float open, float high, float low, float vol)
      : Event("MARKET_EVENT"), m_open(open), m_high(high), m_low(low),
        m_volume(vol), m_symbol(symbol) {}

  float getDayAverage() const { return (m_low + m_high) / 2; }

  string toString() {
    std::stringstream stream;
    stream << " MarketEvent {open: " << std::fixed << std::setprecision(2)
           << m_open << " high: " << m_high << " low: " << m_low
           << " volume: " << m_volume << "}";

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

class SignalEvent : public Event {

public:
  OrderType m_type;
  Security m_security;

  SignalEvent(OrderType type, Security sec)
      : Event("SIGNAL_EVENT"), m_type(type), m_security(sec) {}
  ~SignalEvent() {}

  string toString() {
    switch (m_type) {
    case BUY: {
      return "BUY " + m_security.symbol;
    }
    case SELL: {
      return "SELL " + m_security.symbol;
    }
    case HOLD: {
      return "HOLD  " + m_security.symbol;
    }
    }

    return "HOLD  " + m_security.symbol;
  }

  string toString() const {
    switch (m_type) {
    case BUY: {
      return "BUY " + m_security.symbol;
    }
    case SELL: {
      return "SELL " + m_security.symbol;
    }
    case HOLD: {
      return "HOLD  " + m_security.symbol;
    }
    }

    return "HOLD  " + m_security.symbol;
  }
};

class OrderEvent : public Event {
public:
  Security m_security;
  unsigned long long m_quantity;
  OrderType m_order_type;

  OrderEvent(Security sec, unsigned long quantity, OrderType type)
      : Event("ORDER_EVENT"), m_security(sec), m_quantity(quantity),
        m_order_type(type) {}
  ~OrderEvent() {}

  string toString() {

    std::stringstream ret;
    switch (m_order_type) {
    case BUY:
      ret << "BUY";
      break;
    case SELL:
      ret << "SELL";
      break;
    case HOLD:
      ret << "HOLD";
      break;
    }

    ret << " " << m_quantity << " " << m_security.symbol << " @ "
        << "$" << std::fixed << std::setprecision(2) << m_security.price;
    return ret.str();
  }

  string toString() const {

    std::stringstream ret;
    switch (m_order_type) {
    case BUY:
      ret << "BUY";
      break;
    case SELL:
      ret << "SELL";
      break;
    case HOLD:
      ret << "HOLD";
      break;
    }

    ret << " " << m_quantity << " " << m_security.symbol << " @ "
        << "$" << std::fixed << std::setprecision(2) << m_security.price;
    return ret.str();
  }
};

extern EventQueue event_queue;

#endif
