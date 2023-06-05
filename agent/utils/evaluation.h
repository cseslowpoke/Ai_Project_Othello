#pragma once
#include "bitboard.h"
class evaluation {
public:
  virtual int eval(bitboard b) = 0;
};

class simpleEvaluation : public evaluation {
public:
  int eval(bitboard b);
};

class normalEvaluation : public evaluation {
public:
  int eval(bitboard b);

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
