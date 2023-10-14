#include "nlohmann/json.hpp"
#include "strategy.h"
#include <vector>

#ifndef BACKTEST_H
#define BACKTEST_H

using json = nlohmann::json;
using std::vector;

class Backtest {
private:
  json m_config;
  vector<shared_ptr<Strategy>> m_strategies;

public:
  Backtest(json &config);
  ~Backtest() {}

  void run();
};

#endif
