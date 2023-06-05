#pragma once
#include "ai.h"
#include "utils/bitboard.h"
#include "utils/evaluation.h"
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
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
  ull na_search(bitboard& b);
  int nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta);
  ull nat_search(bitboard& b);
  int nega_alpha_transpose(bitboard &b, int depth, bool passed, int alpha, int beta);
  int nega_scout(bitboard &b, int depth, bool passed, int alpha, int beta);
  void name();
  inline int calc_move_ordering_value(const bitboard b);
private:
  int depth = 9;
  evaluation *e;
  std::unordered_map<bitboard, int, bitboard::hash> transpose_table_upper;          
  std::unordered_map<bitboard, int, bitboard::hash> transpose_table_lower;          
  std::unordered_map<bitboard, int, bitboard::hash> former_transpose_table_upper; 
  std::unordered_map<bitboard, int, bitboard::hash> former_transpose_table_lower;     
};

