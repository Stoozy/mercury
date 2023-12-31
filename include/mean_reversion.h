#ifndef MEAN_REVERSION_H
#define MEAN_REVERSION_H

#include "nlohmann/json.hpp"
#include "strategy.h"

using json = nlohmann::json;

class MeanReversion : public Strategy {
private:
  // simple moving avg, weighted moving avg, exponential moving avg.
  enum { SMA, EMA } m_type;
  unsigned long long m_short_term;
  unsigned long long m_long_term;
  unsigned long long m_cur_day;
  float m_slippage;
  float m_transaction_cost;
  float m_smoothing; // used for calculating EMA

public:
  MeanReversion(const json &config);

  SignalEvent calculateSMA(const MarketEvent);
  SignalEvent calculateEMA(const MarketEvent);

  virtual void calculateSignal(const MarketEvent);
  virtual void executeSignal(const SignalEvent);

  virtual void updatePortfolio(const MarketEvent);
  virtual void updatePortfolio(const OrderEvent);

  virtual void onEvent(const EventVariant event);
};

#endif