#include "simple_eval.h"

int simple_eval::eval(bitboard b) {
  return __builtin_popcountll(b.playerBoard) -
          __builtin_popcountll(b.opponentBoard);
}