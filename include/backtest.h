#include "nlohmann/json.hpp"
#include "strategy.h"
#include <vector>

#ifndef BACKTEST_H
#define BACKTEST_H

using json = nlohmann::json;
using std::vector;

typedef struct {
  float profit;
  float loss;
} PNL;

class Backtest {
private:
  json m_config;
  vector<PNL> m_results;
  vector<shared_ptr<Strategy>> m_strategies;

public:
  Backtest(json &config);
  ~Backtest() {}

  vector<PNL> getResults();
  void run();
};

#endif
