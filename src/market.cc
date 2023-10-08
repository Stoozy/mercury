#include <clue.h>
#include <market.h>
#include <unistd.h>

MarketSimulation::MarketSimulation(const json &config) : m_config(config) {}
MarketSimulation::~MarketSimulation() {}

void MarketSimulation::run() {
  LOG_INFO("[MARKET_SIMULATION] Started market simulation.");

  for (;;) {
    Event event("MARKET_EVENT");
    event_queue.push(event);
    sleep(2);
    LOG_INFO("[MarketSim] Fired event " << event.toString());
  }
}
