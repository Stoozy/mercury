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

  auto start = util::parse_date(m_config["start_date"]);
  auto end = util::parse_date(m_config["end_date"]);

  // Calculate the duration between the two time points
  auto duration = end - start;

  int days =
      std::chrono::duration_cast<std::chrono::duration<int>>(duration).count() /
      (60 * 60 * 24);

  LOG_INFO("Simulating " << days << " days worth of data.");

  string file = m_config["historical_data"];
  string symbol = file.substr(0, file.find(".")); // get symbol from file name

  io::CSVReader<5> in(file);
  in.read_header(io::ignore_extra_column, "Date", "Open", "High", "Low",
                 "Volume");
  std::string date;
  float open;
  float high;
  float low;
  float volume;
  while (in.read_row(date, open, high, low, volume)) {
    auto cur = util::parse_date(date);
    if (start <= cur && cur <= end) {
      MarketEvent me(symbol, open, high, low, volume);
      EventVariant variant = me;
      event_queue.push(variant);
    }
  }

  QuitEvent qe;
  EventVariant variant = qe;
  event_queue.push(variant);
}
