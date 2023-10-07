#include <clue.h>
#include <mean_reversion.h>

MeanReversion::MeanReversion(const json &config) : Strategy(config) {
  if (!config.contains("moving-average")) {
    LOG_CRITICAL("Invalid mean reversion strategy parameters");
    exit(-1);
  }
}

void MeanReversion::calculateEMA() {}
void MeanReversion::calculateWMA() {}
void MeanReversion::calculateSMA() {}

void MeanReversion::calculateSignals() {
  switch (type) {
  case WMA:
    return calculateWMA();
  case EMA:
    return calculateEMA();
  case SMA:
    return calculateSMA();
  }
}

void MeanReversion::executeSignals() {}
void MeanReversion::updatePortfolio() {}

void MeanReversion::onEvent(const Event &event) {}