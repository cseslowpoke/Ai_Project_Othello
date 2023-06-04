#pragma once
#include <string>
class ai {
public:
  ai(int _player) { player = _player; }
  virtual int move(std::string board) = 0;
  int player;
  virtual void name() = 0;
};
