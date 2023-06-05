#pragma once
#include "ai.h"
#include "utils/bitboard.h"
#include "utils/evaluation.h"
#include "search_method/search_method_factor.h"
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

class dai : public ai {
public:
  dai(int _player) : ai(_player) {
    player = _player;
    search = search_factor::create_method(NEGA_ALPHA);
  }
  int move(std::string board);
  void name();
private:
  search_method* search;  
};

