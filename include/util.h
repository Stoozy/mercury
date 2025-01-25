#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <list>

#define PROFILE

#define VERSION "Mercury v1"
#define USAGE                                                                  \
  "Proper Usage:\n\
\tmercury -c <config-file>\n\
\nAdditional flags:\n\
\t-v \tshow version\n\
\t-h \tdisplay this guide\n\
\t-c \tset config file"

namespace util {
std::string char_ptr_to_string(const char *str);
std::chrono::system_clock::time_point parse_date(const std::string &dateString);

float get_fp_avg_vec(std::vector<float> v);
float get_fp_avg_list(std::list<float> l);

}

#endif
