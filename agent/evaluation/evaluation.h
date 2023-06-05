#pragma once
#include <iostream>
#include "../utils/bitboard.h"
class evaluation {
public:
  virtual int eval(bitboard b) = 0;
  virtual void name() = 0;
};


