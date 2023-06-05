#include "nega_alpha.h"

ull nega_alpha::search(bitboard& b) {
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  ull maxput = 0;
  while (legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    int score = -search_nega_alpha(tmp, depth - 1, false, -10000000, 10000000);
    if (score > maxscore) {
      maxscore = score;
      maxput = put;
    }
  }
  return maxput;
}

int nega_alpha::search_nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta) {
  if (depth == 0) {
    return e->eval(b);
  }
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  while (legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    int score = -search_nega_alpha(tmp, depth - 1, false, -beta, -alpha);
    if (score >= beta) {
      return beta;
    }
    alpha = std::max(alpha, score);
    maxscore = std::max(maxscore, score);
  }

  if (maxscore == -10000000) {
    if (passed) {
      return e->eval(b);
    }
    bitboard tmp = b;
    tmp.swap();
    return -search_nega_alpha(tmp, depth, true, -beta, -alpha);
  }
  return maxscore;
}
 