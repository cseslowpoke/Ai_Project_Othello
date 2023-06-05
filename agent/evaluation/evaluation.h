#pragma once
#include "../utils/bitboard.h"
class evaluation {
public:
  virtual int eval(bitboard b) = 0;
};


