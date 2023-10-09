#ifndef MEAN_REVERSION_H
#define MEAN_REVERSION_H

#include "nlohmann/json.hpp"
#include "strategy.h"

using json = nlohmann::json;

class MeanReversion : public Strategy {
private:
  // simple moving avg, weighted moving avg, exponential moving avg.
  enum { SMA, WMA, EMA } type;

public:
  MeanReversion(const json &config);

  void calculateSMA();
  void calculateWMA();
  void calculateEMA();

  virtual void calculateSignals();
  virtual void executeSignals();
  virtual void updatePortfolio();

  virtual void onEvent(const Event *event);
};

#endif