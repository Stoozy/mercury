#include "nlohmann/json.hpp"
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

public:
  Backtest(json &config) : m_config(config){};
  ~Backtest() {}

  vector<PNL> getResults();
  void run();
};

#endif
