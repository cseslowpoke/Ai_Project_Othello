#pragma once
#include "bitboard.hpp"
class evaluation {
  public:
  virtual int eval(bitboard b) = 0;
};

class simpleEvaluation: public evaluation {
  public:
  int eval(bitboard b) {
    return __builtin_popcountll(b.playerBoard) - __builtin_popcountll(b.opponentBoard);
  }
};