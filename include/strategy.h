#include "events.h"
#include "nlohmann/json.hpp"

#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <vector>

using json = nlohmann::json;
using std::string;
using std::vector;

typedef struct asset {
  string symbol;
  float price;
} Asset;

typedef enum OrderType { BUY, SELL } OrderType;

class Strategy : public EventListener {
private:
  vector<Event> signals;
  vector<Asset> portfolio;
  const json &m_config;

public:
  Strategy(const json &config) : m_config(config), EventListener("") {}
  ~Strategy() {}

  virtual void calculateSignals() = 0;
  virtual void executeSignals() = 0;
  virtual void updatePortfolio() = 0;

  virtual void onEvent(const Event &event) { signals.push_back(event); }
};

#endif