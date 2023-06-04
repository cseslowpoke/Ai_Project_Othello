#include "evaluation.h"

int simpleEvaluation::eval(bitboard b) {
  return __builtin_popcountll(b.playerBoard) -
          __builtin_popcountll(b.opponentBoard);
}

int normalEvaluation::eval(bitboard b) {
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