#pragma once

// make a bitboard class
using ull = unsigned long long;
class bitboard {
public:
  int player = 0;
  ull playerBoard = 0, opponentBoard = 0;
  bitboard() {}
  void setBoard(ull _playerBoard, ull _opponentBoard);
  bool canPut(ull put);
  void reverse(ull put);
  ull makeLegalBoard();
  void swap();
  ull transfer(ull, int);
};
