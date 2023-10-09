#include <thread>

#include <backtest.h>
#include <clue.h>
#include <data_handler.h>
#include <market.h>
#include <mean_reversion.h>

vector<PNL> Backtest::getResults() { return m_results; }

void Backtest::run() {
  DataHandler data_handler;

  json strategy_config = m_config["strategy"];
  LOG_INFO("Got strategy config " << strategy_config);

  for (auto strategy : m_strategies) {
    if (strategy.get()->m_name == strategy_config["name"]) {
      LOG_INFO("Found " << strategy_config["name"] << " strategy.");
      data_handler.addListener(strategy);
    }
  }

  std::thread(&MarketSimulation::run, MarketSimulation(m_config)).detach();

  data_handler.run();
}

Backtest::Backtest(json &config) : m_config(config) {
  json strategy_config = m_config["strategy"];

  // add new strategies here
  m_strategies.push_back(std::make_shared<MeanReversion>(strategy_config));
};
