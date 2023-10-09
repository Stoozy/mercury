#include <events.h>

EventQueue::EventQueue() {}
EventQueue::~EventQueue() {}

const size_t EventQueue::size() {
  m_mutex.lock();
  size_t size = m_queue.size();
  m_mutex.unlock();

  return size;
}

void EventQueue::push(EventVariant &event) {
  m_mutex.lock();
  m_queue.push(event);
  m_mutex.unlock();
}

const EventVariant EventQueue::pop() {
  m_mutex.lock();
  auto first = m_queue.front();
  m_queue.pop();

  m_mutex.unlock();
  return first;
}

EventQueue event_queue;