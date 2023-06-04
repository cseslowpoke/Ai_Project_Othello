#pragma once
#include "ai.hpp"
#include "utils/bitboard.h"
#include "utils/evaluation.h"
#include <chrono>
#include <iostream>
class dai : public ai {
public:
  dai(int _player) : ai(_player) {
    e = new normalEvaluation();
    player = _player;
  }
  dai(int _player, evaluation *_e) : ai(_player) {
    e = _e;
    player = _player;
  }
  int move(std::string board);
  int nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta);
  void name() { std::cout << "dai" << std::endl; }

private:
  int depth = 10;
  evaluation *e;
};

