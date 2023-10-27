#include <catch2/catch_test_macros.hpp>
#include <events.h>
#include <data_handler.h>
#include <memory>
#include <iostream>

std::vector<EventVariant> events_received;
TEST_CASE("DataHandler", "[DATA_HANDLER]"){

    class TestEventListener: public EventListener {
        public:
        TestEventListener(): EventListener("TestEventListener"){}
        ~TestEventListener(){}
    
         void onEvent(const EventVariant event) {
            events_received.push_back(event);
        }
    };

    DataHandler dh;
    TestEventListener listener;

    float r1 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r3 = rand() % 100 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    float rv = rand() % 1000000 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    // quit event to prevent data handler from running forever
    EventVariant event_variants[] = { 
        MarketEvent("TEST_EVENT_1", r1, r1, r1, rv),
        MarketEvent("TEST_EVENT_2", r2, r2, r2, rv),
        MarketEvent("TEST_EVENT_3", r3, r3, r3, rv),
        QuitEvent(),
    };

    for(auto ev: event_variants)
        event_queue.push(ev);

    dh.addListener(std::make_shared<TestEventListener>(listener));
    dh.run();

    shared_ptr<EventListener> el (std::make_shared<TestEventListener>(listener));

    // make sure all the events are there
    REQUIRE(events_received.size() == 3);

    // test the order of the events and correct values
    auto ev = events_received.back();
    REQUIRE(ev.index() == MARKET_EVENT);
    REQUIRE(std::get<MarketEvent>(ev).m_symbol == "TEST_EVENT_3");
    REQUIRE(std::get<MarketEvent>(ev).getDayAverage() == r3);
    events_received.pop_back();


    ev = events_received.back();
    REQUIRE(ev.index() == MARKET_EVENT);
    REQUIRE(std::get<MarketEvent>(ev).m_symbol == "TEST_EVENT_2");
    REQUIRE(std::get<MarketEvent>(ev).getDayAverage() == r2);
    events_received.pop_back();

    ev = events_received.back();
    REQUIRE(ev.index() == MARKET_EVENT);
    REQUIRE(std::get<MarketEvent>(ev).m_symbol == "TEST_EVENT_1");
    REQUIRE(std::get<MarketEvent>(ev).getDayAverage() == r1);
    events_received.pop_back();
}

