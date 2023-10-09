#include <algorithm>
#include <clue.h>
#include <data_handler.h>
#include <memory>
#include <unistd.h>

using std::find_if;
using std::make_unique;

DataHandler::DataHandler() {}
DataHandler::~DataHandler() {}

void DataHandler::addListener(shared_ptr<EventListener> listener) {
  m_listeners.push_back(std::move(listener));
}

void DataHandler::removeListener(shared_ptr<EventListener> listener) {
  auto object = find_if(
      m_listeners.begin(), m_listeners.end(),
      [&listener](shared_ptr<EventListener> l) { return l == listener; });

  if (object != m_listeners.end()) {
    m_listeners.erase(object);
  } else {
    LOG_ALERT("Could not find " << (*listener).m_name
                                << " in list of listeners.");
  }
}

void DataHandler::run() {
  // TODO: listen to market events

  for (;;) {
    if (event_queue.size() > 0) {
      auto event = event_queue.pop();

      if (event->type == QUIT_EVENT) {

        LOG_INFO("[DataHandler] Received QUIT_EVENT. Quitting backtest.");
        return;
      }

      LOG_INFO("[DataHandler] Dispatching " << event->toString()
                                            << " to listeners.");
      dispatch(event);
    }

    sleep(0.5);
  }
}

void DataHandler::dispatch(const Event *event) {
  // dispatch to every listener

  for (shared_ptr<EventListener> listener : m_listeners) {
    listener.get()->onEvent(event);
  }
}