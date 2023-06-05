#include "normal_eval_b.h"
int normal_eval_c::eval(bitboard b) {
  int point = 0;
  int pos;
  if (!(~(b.playerBoard | b.opponentBoard))) {
    point = __builtin_popcountll(b.playerBoard) -
            __builtin_popcountll(b.opponentBoard);
    point *= 10000;
  }
  else {
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
  }  
  return point;
}