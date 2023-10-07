#include "nlohmann/json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

#ifndef CONFIG_H
#define CONFIG_H

using std::ifstream;
using std::string;

class Config {
private:
  string m_config_path;
  ifstream m_file;
  json m_data;

public:
  Config(string path) : m_config_path(path) { m_file = ifstream(path); };

  ~Config();

  bool exists();
  bool load();
  json getJson();
};

#endif