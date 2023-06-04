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

void board::move(int move) {
  int flag = 1;
  change = "----------------------------------------------------------------";
  if (move == -1) {
    player = !player;
    return;
  }
  int x = move / 8, y = move % 8;
  for (int i = 0; i < 8; i++) {
    int x_ = x + dir[i][0], y_ = y + dir[i][1];
    while (x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8 &&
           nowBoard[x_ * 8 + y_] == (player ? 'X' : 'O')) {
      x_ += dir[i][0];
      y_ += dir[i][1];
    }
    if (x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8 &&
        nowBoard[x_ * 8 + y_] == (player ? 'O' : 'X')) {
      x_ -= dir[i][0];
      y_ -= dir[i][1];
      while (x_ != x || y_ != y) {
        change[x_ * 8 + y_] = '+';
        nowBoard[x_ * 8 + y_] = (player ? 'O' : 'X');
        x_ -= dir[i][0];
        y_ -= dir[i][1];
        flag = 0;
      }
    }
  }
  change[move] = '+';
  nowBoard[move] = (player ? 'O' : 'X');
  player = !player;
}

void board::result() {
  int black = 0, white = 0;
  for (auto i : nowBoard) {
    if (i == 'X') {
      black++;
    } else if (i == 'O') {
      white++;
    }
  }
  printf("black %d:%d white\n", black, white);
}

void board::game() {
  std::cout << "\n\n\n";
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      std::cout << nowBoard[i * 8 + j] << ' ';
    }
    std::cout << '\n';
  }
  result();
}