#pragma once
#include "bitboard.hpp"
class evaluation {
public:
  virtual int eval(bitboard b) = 0;
};

class simpleEvaluation : public evaluation {
public:
  int eval(bitboard b) {
    return __builtin_popcountll(b.playerBoard) -
           __builtin_popcountll(b.opponentBoard);
  }
};

class normalEvaluation : public evaluation {
public:
  int eval(bitboard b) {
    int point = 0;
    for (int i = 0; i < 64; i++) {
      if (b.playerBoard & 1ULL << i) {
        point += weight[i];
      }
      if (b.opponentBoard & 1ULL << i) {
        point -= weight[i];
      }
    }
    return point;
  }

private:
  // const int weight[64] = {30, -12,  0, -1, -1,  0, -12,  30,
  //                        -12, -15, -3, -3, -3, -3, -15, -12,
  //                          0,  -3,  0, -1, -1,  0,  -3,   0,
  //                         -1,  -3, -1, -1, -1, -1,  -3,  -1,
  //                         -1,  -3, -1, -1, -1, -1,  -3,  -1,
  //                          0,  -3,  0, -1, -1,  0,  -3,   0,
  //                        -12, -15, -3, -3, -3, -3, -15, -12,
  //                         30, -12,  0, -1, -1,  0, -12,  30};
  const int weight[64] = {
      120, -12, 20, 5,  5,  20, -20, 120, -20, -40, -5, -5, -5, -5, -40, -20,
      20,  -5,  15, 3,  3,  15, -5,  20,  5,   -5,  3,  3,  3,  3,  -5,  5,
      5,   -5,  3,  3,  3,  3,  -5,  5,   20,  -5,  15, 3,  3,  15, -5,  20,
      -20, -40, -5, -5, -5, -5, -40, -20, 120, -12, 20, 5,  5,  20, -20, 120};
};
