#include "evaluation.h"

int simpleEvaluation::eval(bitboard b) {
  return __builtin_popcountll(b.playerBoard) -
          __builtin_popcountll(b.opponentBoard);
}

int normalEvaluation::eval(bitboard b) {
  int point = 0;
  int pos;
  while(b.playerBoard) {
    pos = __builtin_ffsll(b.playerBoard) - 1;
    point += weight[pos];
    b.playerBoard &= (b.playerBoard - 1);
  }
  while(b.opponentBoard) {
    pos = __builtin_ffsll(b.opponentBoard) - 1;
    point -= weight[pos];
    b.opponentBoard &= b.opponentBoard - 1;
  }
  // for(int i = 0; i < 64; i++) {
  //   if(b.playerBoard & (1ULL << i)) {
  //     point += weight[i];
  //   }
  //   if(b.opponentBoard & (1ULL << i)) {
  //     point -= weight[i];
  //   }
  // }
    // if (b.playerBoard & (iter & -iter)) {
    //   point += weight[i];
    // }
    // if (b.opponentBoard & 1ULL << i) {
    //   point -= weight[i];
    // }
  
  return point;
}