#include <clue.h>
#include <csv.h>
#include <events.h>
#include <market.h>
#include <time.h>
#include <unistd.h>
#include <util.h>

MarketSimulation::MarketSimulation(const json &config) : m_config(config) {}
MarketSimulation::~MarketSimulation() {}

void MarketSimulation::run() {
  LOG_INFO("[MarketSimulator] Started market simulation.");

  auto start = parse_date(m_config["start_date"]);
  auto end = parse_date(m_config["end_date"]);

  // Calculate the duration between the two time points
  auto duration = end - start;

  int days =
      std::chrono::duration_cast<std::chrono::duration<int>>(duration).count() /
      (60 * 60 * 24);

  LOG_INFO("Days " << days);

  // string data = m_config["historical_data"];
  // LOG_INFO("Historical data at " << data);

  io::CSVReader<4> in(m_config["historical_data"]);
  in.read_header(io::ignore_extra_column, "Date", "Open", "High", "Low");
  std::string Date;
  float Open;
  float High;
  float Low;
  while (in.read_row(Date, Open, High, Low)) {
    // do stuff with the data
    auto cur = parse_date(Date);
    if (start <= cur && cur <= end) {

      LOG_INFO(" Date: " << Date << " Open: " << Open);
    }
  }

  QuitEvent qe;
  EventVariant variant = qe;
  event_queue.push(variant);
}
