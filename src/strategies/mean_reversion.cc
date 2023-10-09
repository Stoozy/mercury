#include <clue.h>
#include <mean_reversion.h>

MeanReversion::MeanReversion(const json &config) : Strategy(config) {
  m_name = "MEAN_REVERSION";

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

void MeanReversion::onEvent(const Event *event) {
  string data;
  switch (event->type) {
  case MARKET_EVENT: {
    const MarketEvent *me = (MarketEvent *)(event);
    LOG_INFO("[MEAN_REVERSION] Recieved event " << me->toString());
    break;
  }
  default:
    break;
  }
}