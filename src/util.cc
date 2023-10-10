#include <clue.h>
#include <string>
#include <util.h>

using std::string;

std::chrono::system_clock::time_point
parse_date(const std::string &dateString) {
  std::tm timeStruct = {};
  std::istringstream ss(dateString);

  //   LOG_DEBUG("Parsing date " << dateString);

  ss >> std::get_time(&timeStruct, "%Y-%m-%d");
  if (ss.fail()) {
    throw std::invalid_argument("Failed to parse the date string.");
  }
  return std::chrono::system_clock::from_time_t(std::mktime(&timeStruct));
}

string char_ptr_to_string(char *str) {
  string s = "";
  int len = strlen(str);

  for (int i = 0; i < len; i++)
    s += str[i];

  return s;
}