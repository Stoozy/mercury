#include <clue.h>
#include <market.h>
#include <unistd.h>

MarketSimulation::MarketSimulation(const json &config) : m_config(config) {}
MarketSimulation::~MarketSimulation() {}

void MarketSimulation::run() {
  LOG_INFO("[MarketSimulator] Started market simulation.");

  for (int i = 0; i < 10; i++) {
    MarketEvent event(10.5, 20.25, 17, 1000);
    event_queue.push(&event);
    sleep(1);
    LOG_INFO("[MarketSimulator] Fired event " << event.toString());
  }

  QuitEvent qe;
  event_queue.push(&qe);
}
