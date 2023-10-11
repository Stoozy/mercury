#include <clue.h>
#include <list>
#include <mean_reversion.h>

MeanReversion::MeanReversion(const json &config)
    : Strategy(config), m_cur_day(0) {
  m_name = "MEAN_REVERSION";
  m_short_term = config["strategy"]["days"]["short_term"];
  m_long_term = config["strategy"]["days"]["long_term"];
  m_capital = config["capital"];

  json params = config["strategy"];
  if (!params.contains("moving_average") || !params.contains("days")) {
    LOG_CRITICAL("Invalid mean reversion strategy parameters");
    exit(-1);
  }

  string ma = m_config["strategy"]["moving_average"];
  if (ma == "SMA") {
    m_type = SMA;
  } else if (ma == "WMA") {
    m_type = WMA;
  } else if (ma == "EMA") {
    m_type = EMA;
  } else {
    LOG_CRITICAL("Invalid mean reversion moving_average (should either be SMA, "
                 "EMA, or WMA)");
    exit(-1);
  }

  auto positions = m_config["positions"];
  for (auto position : positions) {
    Security security = {position["symbol"], position["price"]};
    m_portfolio.push_back(std::make_tuple(security, position["quantity"]));
  }

  for (tuple<Security, int> sec : m_portfolio) {
    LOG_INFO("Position: " << std::get<0>(sec).symbol << " @ " << std::fixed
                          << std::setprecision(2) << std::get<0>(sec).price
                          << " Quantity:" << std::get<1>(sec));
  }
}

SignalEvent MeanReversion::calculateSMA(const MarketEvent event) {
  static std::list<float> long_term_prices;
  static std::list<float> short_term_prices;

  float current_ltp_avg =
      std::accumulate(long_term_prices.begin(), long_term_prices.end(), 0) /
      m_long_term;

  float current_stp_avg =
      std::accumulate(short_term_prices.begin(), short_term_prices.end(), 0) /
      m_short_term;

  if (long_term_prices.size() > m_long_term) {
    long_term_prices.pop_back();
  } else {
    long_term_prices.push_front(event.getDayAverage());
  }

  if (short_term_prices.size() > m_short_term) {
    short_term_prices.pop_back();
  } else {
    short_term_prices.push_front(event.getDayAverage());
  }

  float new_ltp_avg =
      std::accumulate(long_term_prices.begin(), long_term_prices.end(), 0) /
      m_long_term;

  float new_stp_avg =
      std::accumulate(short_term_prices.begin(), short_term_prices.end(), 0) /
      m_short_term;

  Security security = {event.m_symbol, event.getDayAverage()};

  if (current_ltp_avg > current_stp_avg) {
    // short term avg rises above long term avg
    // send SELL signal
    if (new_ltp_avg < new_stp_avg) {
      return SignalEvent(SELL, security);
    }

  } else if (current_ltp_avg < current_stp_avg) {
    // short term avg falls below long term avg
    // send BUY signal
    if (new_ltp_avg > new_stp_avg) {
      return SignalEvent(BUY, security);
    }
  }

  // hold by default
  return SignalEvent(HOLD, security);
}

// SignalEvent MeanReversion::calculateWMA() { // TODO:
// }

// SignalEvent MeanReversion::calculateEMA() { // TODO:
// }

void MeanReversion::calculateSignal(const MarketEvent event) {
  // hold by default
  SignalEvent signal(HOLD, Security{event.m_symbol, event.getDayAverage()});
  switch (m_type) {
  case WMA:
    // signal = calculateWMA();
    break;
  case EMA:
    // signal = calculateEMA();
    break;
  case SMA:
    signal = calculateSMA(event);
    break;
  }

  onEvent(EventVariant(signal));
}

void MeanReversion::executeSignal(const SignalEvent event) {
  if (event.m_type != HOLD) {
    LOG_INFO("[MeanReversion] Executing event " << event.toString());
  }

  switch (event.m_type) {
  case BUY:
    break;
  case SELL:
    break;
  case HOLD:
    break;
  }
}

void MeanReversion::updatePortfolio(const MarketEvent event) {
  LOG_INFO("[MeanReversion] Updating portfolio " << event.toString());
}

void MeanReversion::updatePortfolio(const OrderEvent event) {
  LOG_INFO("[MeanReversion] Updating portfolio " << event.toString());
}

void MeanReversion::onEvent(const EventVariant variant) {
  string data;
  switch (variant.index()) {
  case MARKET_EVENT: {
    m_cur_day++;
    LOG_INFO("[MeanReversion] Day "
             << m_cur_day << " " << std::get<MarketEvent>(variant).toString());

    updatePortfolio(std::get<MarketEvent>(variant));
    calculateSignal(std::get<MarketEvent>(variant));

    break;
  }
  case SIGNAL_EVENT: {
    executeSignal(std::get<SignalEvent>(variant));
    break;
  }
  case ORDER_EVENT: {
    updatePortfolio(std::get<OrderEvent>(variant));
    break;
  }
  default:
    break;
  }
}