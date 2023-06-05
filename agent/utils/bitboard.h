#pragma once
#include <cstddef>
// make a bitboard class
using ull = unsigned long long;
class bitboard {
public:
  bool player = 0;
  int value = 0;
  ull playerBoard = 0, opponentBoard = 0;
  bitboard() {}
  void setBoard(ull _playerBoard, ull _opponentBoard);
  bool canPut(ull put);
  void reverse(ull put);
  ull makeLegalBoard();
  void swap();
  ull transfer(ull, int);
  struct hash {
      typedef size_t result_type;
      size_t operator()(const bitboard& b) const {
          return
            b.playerBoard | b.opponentBoard;
      }
  };
  bool operator==(const bitboard& rhs) const {
      return hash()(*this) == hash()(rhs);
  }
};
