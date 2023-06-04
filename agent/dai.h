#pragma once
#include "ai.h"
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
  void name();
private:
  int depth = 10;
  evaluation *e;
  unordered_map<board, int, board::hash> transpose_table;          // 現在の探索結果を入れる置換表: 同じ局面に当たった時用
  unordered_map<board, int, board::hash> former_transpose_table;   // 前回の探索結果が入る置換表: move orderingに使う
};

