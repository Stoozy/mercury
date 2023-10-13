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

  for (auto strategy : m_strategies) {
    auto tuples = strategy->getTransactions();

    std::cout << strategy->m_name << " Performance:" << std::endl;

    for (auto tuple : tuples) {
      OrderEvent order = std::get<0>(tuple);
      int day = std::get<1>(tuple);

      std::cout << "\tDay: " << day << "; Order: " << order.toString()
                << std::endl;
    }

    float initial_balance = strategy->m_initial_total;
    float current_balance = strategy->getTotalBalance();

    std::cout << "\tInitial value on all assets: $" << std::fixed
              << std::setprecision(2) << initial_balance << std::endl;

    std::cout << "\tFinal value on all assets: $" << std::fixed
              << std::setprecision(2) << current_balance << std::endl;
  }
}

Backtest::Backtest(json &config) : m_config(config) {
  // json strategy_config = m_config["strategy"];

  // add new strategies here
  m_strategies.push_back(std::make_shared<MeanReversion>(config));
};
