#include <string>
using std::string;

#ifndef TYPES_H
#define TYPES_H

typedef struct security {
  string symbol;
  float price;
} Security;

typedef enum { BUY, SELL, HOLD } OrderType;

#endif
