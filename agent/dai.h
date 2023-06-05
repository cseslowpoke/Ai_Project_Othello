#pragma once
#include "ai.h"
#include "utils/bitboard.h"
#include "utils/evaluation.h"
#include "search_method/search_method_factor.h"
#include <iostream>

class dai : public ai {
public:
  dai(int _player) : ai(_player) {
    player = _player;
    search = search_factor::create_method(NEGA_ALPHA_T);
  }
  dai(int _player, int method) : ai(_player) {
    player = _player;
    search = search_factor::create_method(method_type(method));
  }
  int move(std::string board);
  void name();
private:
  search_method* search;  
};