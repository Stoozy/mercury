#include "events.h"
#include "nlohmann/json.hpp"
#include <thread>

#ifndef MARKET_H
#define MARKTE_H

using json = nlohmann::json;

class MarketSimulation {
private:
  const json m_config;

public:
  MarketSimulation(const json &config);
  ~MarketSimulation();

  void run();
};

#endif