#include <vector>
#include <memory>

#ifndef EVENT_H
#define EVENT_H

class EventListener;

typedef enum event_type {
    MARKET_EVENT,
    SIGNAL_EVENT,
    ORDER_EVENT,
    EXECUTION_EVENT
} EventType;

class Event {
public:
    virtual ~Event();
    virtual std::string getName();
};

class EventDispatcher {
    private:
        std::vector<std::unique_ptr<EventListener>> m_listeners;
    public:
        EventDispatcher();
        virtual ~EventDispatcher();

        virtual void addListener(EventListener * listener);
        virtual void removeListener(EventListener * listener);
        virtual void dispatch();
};

class EventListener {
public:
    ~EventListener();
    virtual void onEvent(const EventType& event) = 0;
};


#endif