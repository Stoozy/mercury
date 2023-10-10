#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>

#define VERSION "Mercury v1"
#define USAGE                                                                  \
  "Proper Usage:\n\
\tmercury -c <config-file>\n\
\nAdditional flags:\n\
\t-v \tshow version\n\
\t-h \tdisplay this guide\n\
\t-c \tset config file"

std::string char_ptr_to_string(char *str);

std::chrono::system_clock::time_point parse_date(const std::string &dateString);

int add(int x, int y);

#endif