#pragma once
#include "../utils/bitboard.h"
#include "../utils/evaluation.h"
#include <algorithm>
using ull=unsigned long long;
class search_method{
  public:
  search_method(){}
  virtual ull search(bitboard& b) = 0;
  const int depth = 0;
  evaluation* e;
};