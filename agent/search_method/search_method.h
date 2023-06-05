#pragma once
#include "../utils/bitboard.h"
#include "../evaluation/eval_factor.h"
#include <algorithm>
using ull=unsigned long long;
class search_method{
  public:
  search_method(){}
  search_method(int eval){
    e = eval_factor::create_eval(eval_type(eval));
  };
  virtual ull search(bitboard& b) = 0;
  const int depth = 0;
  evaluation* e;
};