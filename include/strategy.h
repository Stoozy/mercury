#include "events.h"
#include "nlohmann/json.hpp"

#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <vector>

using json = nlohmann::json;
using std::string;
using std::tuple;
using std::vector;

class Strategy : public EventListener {
protected:
  vector<tuple<Security, int>> m_portfolio;
  const json &m_config;

public:
  Strategy(const json &config) : EventListener(""), m_config(config) {}
  ~Strategy() {}

  virtual void calculateSignal(const MarketEvent) = 0;
  virtual void executeSignal(const SignalEvent) = 0;

  virtual void updatePortfolio(const MarketEvent) = 0;
  virtual void updatePortfolio(const OrderEvent) = 0;

  virtual void onEvent(const EventVariant event) = 0;
};

#endif