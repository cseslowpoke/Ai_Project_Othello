#pragma once
#include "ai.h"
#include "utils/bitboard.h"
#include "evaluation/evaluation.h"
#include "search_method/search_method_factor.h"
#include <iostream>

class dai : public ai {
public:
  dai(int _player, int method = 0, int eval = 1) : ai(_player) {
    player = _player;
    search = search_factor::create_method(method_type(method), eval);
  }
  int move(std::string board);
  void name();
private:
  search_method* search;  
};