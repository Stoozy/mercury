#include <backtest.h>

vector<PNL> Backtest::getResults() { return m_results; }

void Backtest::run() {
  // DUMMY DATA
  m_results.push_back(PNL{10.13, 4.17});
  m_results.push_back(PNL{15.25, 11.78});
  m_results.push_back(PNL{12.85, 8.23});
}
