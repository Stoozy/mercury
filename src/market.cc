#include <clue.h>
#include <market.h>
#include <unistd.h>

void market_sim_main() {
  LOG_INFO("Started market simulation.");

  for (;;) {
    event_queue.push(Event("MARKET_EVENT"));
    sleep(2);
  }
}