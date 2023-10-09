#include <clue.h>
#include <market.h>
#include <unistd.h>

MarketSimulation::MarketSimulation(const json &config) : m_config(config) {}
MarketSimulation::~MarketSimulation() {}

void MarketSimulation::run() {
  LOG_INFO("[MarketSimulator] Started market simulation.");

  for (int i = 0; i < 10; i++) {
    MarketEvent me(10.5, 20.25, 17, 1000);
    EventVariant variant = me;
    event_queue.push(variant);
    sleep(1);
    LOG_INFO("[MarketSimulator] Fired event " << me.toString());
  }

  QuitEvent qe;
  EventVariant variant = qe;
  event_queue.push(variant);
}
