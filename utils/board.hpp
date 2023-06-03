#pragma once
#include <string>
class board {
  public:
    board() {
      nowBoard = "---------------------------OX------XO---------------------------";
      change = "----------------------------------------------------------------";
      player = 0;
    }
    void move(int);
    std::string nowBoard;
    std::string change;
  private:
  int player;
  const int dir[8][2] = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                         {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
  // const int dir[8] = {-8, -7, 1, 9, 8, 7, -1, -9};
};


void board::move(int move) {
  change = "----------------------------------------------------------------";
  if (move == -1) {
    player = !player;
    return;
  }
  int x = move / 8, y = move % 8;
  for (int i = 0; i < 8; i++) {
    int x_ = x + dir[i][0], y_ = y + dir[i][1];
    while(x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8 && nowBoard[x_ * 8 + y_] == (player ? 'X' : 'O')) {
      x_ += dir[i][0];
      y_ += dir[i][1];
    }
    if(x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8 && nowBoard[x_ * 8 + y_] == (player ? 'O' : 'X')) {
      x_ -= dir[i][0];
      y_ -= dir[i][1];
      while(x_ != x || y_ != y) {
        change[x_ * 8 + y_] = '+';
        nowBoard[x_ * 8 + y_] = (player ? 'O' : 'X');
        x_ -= dir[i][0];
        y_ -= dir[i][1];
      }
    }
  }
  change[move] = '+';
  nowBoard[move] = (player ? 'O' : 'X');
  player = !player;
}