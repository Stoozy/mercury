#include <clue.h>
#include <config.h>
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
  try {
    m_data = json::parse(m_file);

  } catch (json::parse_error err) {
    return false;
  }

  if (!m_data.contains("historical_data") || !m_data.contains("strategy") ||
      !m_data.contains("positions") || !m_data.contains("start_date") ||
      !m_data.contains("end_date")) {
    return false;
  }

  for (string path : m_data["historical_data"])
    LOG_INFO("Using " << path << " for historical data");

  return true;
}

json Config::getJson() { return m_data; }