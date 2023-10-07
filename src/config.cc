#include <cfg.h>
#include <clue.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using std::string;

Config::~Config() {}

bool Config::exists() {
  std::ifstream infile(m_config_path);
  return infile.good();
}

bool Config::load() {
  json data;
  try {
    data = json::parse(m_file);
  } catch (json::parse_error err) {
    return false;
  }

  if (!data.contains("historical_data") || !data.contains("strategy") ||
      !data.contains("positions") || !data.contains("start_date") ||
      !data.contains("end_date")) {
    return false;
  }

  for (string path : data["historical_data"])
    LOG_INFO("Using " << path << " for historical data");

  return true;
}