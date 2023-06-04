#include "dai.h"
void dai::name() {
  std::cout << "dai2" << std::endl;
}
int dai::move(std::string checker) {
  ull black = 0, white = 0;
  bitboard b;
  for (int i = 0; i < 64; i++) {
    if (checker[i] == 'X') {
      black |= (1ULL << i);
    } else if (checker[i] == 'O') {
      white |= (1ULL << i);
    }
  }
  if (player == 1) {
    b.setBoard(white, black);
  } else {
    b.setBoard(black, white);
  }
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  ull maxput = 0;
  while (legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    int score = -nega_alpha(tmp, depth - 1, false, -10000000, 10000000);
    if (score > maxscore) {
      maxscore = score;
      maxput = put;
    }
  }

  for (int i = 0; i < 64; i++) {
    if (maxput & (1ULL << i)) {
      return i;
    }
  }
  return -1;
}

int dai::nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta) {
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
    int score = -nega_alpha(tmp, depth - 1, false, -beta, -alpha);
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
    return -nega_alpha(tmp, depth, true, -beta, -alpha);
  }
  return maxscore;
}