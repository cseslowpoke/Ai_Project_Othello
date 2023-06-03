#pragma once
#include "utils/bitboard.hpp"
#include "utils/evaluation.hpp"
#include "ai.hpp"

class dai : public ai {
  public:
    dai(int _player): ai(_player) {
      e = new simpleEvaluation();
      player = _player;
    }
    int move(std::string board);
    int negaalpha(bitboard b, int depth, bool passed, int alpha, int beta);
    void name() {
      std::cout << "dai" << std::endl;
    }
  private:
    int depth = 10;
    evaluation* e;
};

int dai::move(std::string checker) {
  ull black = 0, white = 0;
  bitboard b;
  for (int i = 0; i < 64; i++) {
    if (checker[i] == 'X') {
      black |= (1ULL << i);
    }
    else if (checker[i] == 'O') {
      white |= (1ULL << i);
    }
  }
  if (player == 1) {
    b.setBoard(white, black);
  }
  else {
    b.setBoard(black, white);
  }
  ull c = b.makeLegalBoard();
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  ull maxput = 0;
  while(legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    int score = -negaalpha(tmp, depth - 1, false, -10000000, 10000000);
    if (score > maxscore) {
      maxscore = score;
      maxput = put;
    }
  }
  for(int i = 0; i < 64; i++) {
    if (maxput & (1ULL << i)) {
      return i;
    }
  }
  return -1;
}

int dai::negaalpha(bitboard b, int depth, bool passed, int alpha, int beta) {
  if (depth == 0) {
    return e->eval(b);
  }
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  while(legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    int score = -negaalpha(tmp, depth - 1, false, -beta, -alpha);
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
    return -negaalpha(tmp, depth, true, -beta, -alpha);
  }
  return maxscore;
}


