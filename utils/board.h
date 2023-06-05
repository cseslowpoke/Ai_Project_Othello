#pragma once
#include <iostream>
#include <string>
class board {
public:
  board() {
    nowBoard =
        "---------------------------OX------XO---------------------------";
    change = "----------------------------------------------------------------";
    player = 0;
  }
  void move(int);
  void result();
  void game();
  std::string nowBoard;
  std::string change;

private:
  int player;
  const int dir[8][2] = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                         {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
  // const int dir[8] = {-8, -7, 1, 9, 8, 7, -1, -9};
};
