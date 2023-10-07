#ifndef UTIL_H
#define UTIL_H

#include <string>

#define VERSION  "Mercury v1"
#define USAGE "Proper Usage:\n\
\tmercury -c <config-file>\n\
\nAdditional flags:\n\
\t-v \tshow version\n\
\t-h \tdisplay this guide\n\
\t-c \tset config file"



std::string char_ptr_to_string(char * str);

int add(int x, int y);

#endif