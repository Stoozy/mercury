#include "events.h"
#include "nlohmann/json.hpp"

#ifndef STRATEGY_H
#define STRATEGY_H

#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;
using std::string;
using std::tuple;
using std::vector;

class Strategy : public EventListener {
protected:
  // <security, number of said security>
  vector<tuple<Security, int>> m_portfolio;
  float m_capital;

  // <order, day>
  vector<tuple<OrderEvent, int>> m_orders;
  std::ofstream m_output_file;
  const json &m_config;

public:
  float m_initial_total;

  Strategy(const json &config) : EventListener(""), m_config(config) {}
  ~Strategy() {}

  vector<tuple<OrderEvent, int>> getTransactions() { return m_orders; }
  vector<tuple<Security, int>> getPortfolio() { return m_portfolio; }
  float getCapital() { return m_capital; }

  float getTotalBalance() {
    float ret = m_capital;
    for (auto tuple : m_portfolio) {
      int count = std::get<1>(tuple);
      float price = std::get<0>(tuple).price;

      ret += (count * price);
    }

    return ret;
  }

  virtual void calculateSignal(const MarketEvent) = 0;
  virtual void executeSignal(const SignalEvent) = 0;

  virtual void updatePortfolio(const MarketEvent) = 0;
  virtual void updatePortfolio(const OrderEvent) = 0;

  virtual void onEvent(const EventVariant event) = 0;
};

#endif