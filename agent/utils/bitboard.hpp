#pragma once

// make a bitboard class
using ull=unsigned long long;

ull transfer(ull put, int k) {
  switch(k) {
    case 0: //上
      return (put << 8) & 0xffffffffffffff00;
    case 1: //右上
      return (put << 7) & 0x7f7f7f7f7f7f7f00;
    case 2: //右
      return (put >> 1) & 0x7f7f7f7f7f7f7f7f;
    case 3: //右下
      return (put >> 9) & 0x007f7f7f7f7f7f7f;
    case 4: //下
      return (put >> 8) & 0x00ffffffffffffff;
    case 5: //左下
      return (put >> 7) & 0x00fefefefefefefe;
    case 6: //左
      return (put << 1) & 0xfefefefefefefefe;
    case 7: //左上
      return (put << 9) & 0xfefefefefefefe00;
    default:
      return 0;
  }
}

class bitboard {
  public:
    int player = 0;
    ull playerBoard = 0, opponentBoard = 0;
    bitboard(){}
    void setBoard(ull _playerBoard, ull _opponentBoard);
    bool canPut(ull put);
    void reverse(ull put);
    ull makeLegalBoard();
    void swap();
  private:
};

void bitboard::reverse(ull put) {
  ull rev = 0;
  for (int i = 0; i < 8; i++) {
    ull rev_ = 0;
    ull mask = transfer(put, i);
    while (mask != 0 && (mask & opponentBoard)) {
      rev_ |= mask;
      mask = transfer(mask, i);
    }
    if ((mask & playerBoard) != 0) {
      rev |= rev_;
    }
  }
  playerBoard ^= put | rev;
  opponentBoard ^= rev;
}

ull bitboard::makeLegalBoard() {
  ull horiBoard = opponentBoard & 0x7e7e7e7e7e7e7e7e;
  ull vertBoard = opponentBoard & 0x00ffffffffffff00;
  ull aSideBoard = opponentBoard & 0x007e7e7e7e7e7e00;
  ull blankBoard = ~(playerBoard | opponentBoard);
  ull tmp;
  ull legalBoard = 0;

  //left
  tmp = horiBoard & (playerBoard << 1);
  tmp |= horiBoard & (tmp << 1);
  tmp |= horiBoard & (tmp << 1);
  tmp |= horiBoard & (tmp << 1);
  tmp |= horiBoard & (tmp << 1);
  tmp |= horiBoard & (tmp << 1);
  legalBoard = blankBoard & (tmp << 1);

  //right
  tmp = horiBoard & (playerBoard >> 1);
  tmp |= horiBoard & (tmp >> 1);
  tmp |= horiBoard & (tmp >> 1);
  tmp |= horiBoard & (tmp >> 1);
  tmp |= horiBoard & (tmp >> 1);
  tmp |= horiBoard & (tmp >> 1);
  legalBoard |= blankBoard & (tmp >> 1);

  //top
  tmp = vertBoard & (playerBoard << 8);
  tmp |= vertBoard & (tmp << 8);
  tmp |= vertBoard & (tmp << 8);
  tmp |= vertBoard & (tmp << 8);
  tmp |= vertBoard & (tmp << 8);
  tmp |= vertBoard & (tmp << 8);
  legalBoard |= blankBoard & (tmp << 8);

  //down
  tmp = vertBoard & (playerBoard >> 8);
  tmp |= vertBoard & (tmp >> 8);
  tmp |= vertBoard & (tmp >> 8);
  tmp |= vertBoard & (tmp >> 8);
  tmp |= vertBoard & (tmp >> 8);
  tmp |= vertBoard & (tmp >> 8);
  legalBoard |= blankBoard & (tmp >> 8);

  // right top
  tmp = aSideBoard & (playerBoard << 7);
  tmp |= aSideBoard & (tmp << 7);
  tmp |= aSideBoard & (tmp << 7);
  tmp |= aSideBoard & (tmp << 7);
  tmp |= aSideBoard & (tmp << 7);
  tmp |= aSideBoard & (tmp << 7);
  legalBoard |= blankBoard & (tmp << 7);

  tmp = aSideBoard & (playerBoard << 9);
  tmp |= aSideBoard & (tmp << 9);
  tmp |= aSideBoard & (tmp << 9);
  tmp |= aSideBoard & (tmp << 9);
  tmp |= aSideBoard & (tmp << 9);
  tmp |= aSideBoard & (tmp << 9);
  legalBoard |= blankBoard & (tmp << 9);

  tmp = aSideBoard & (playerBoard >> 9);
  tmp |= aSideBoard & (tmp >> 9);
  tmp |= aSideBoard & (tmp >> 9);
  tmp |= aSideBoard & (tmp >> 9);
  tmp |= aSideBoard & (tmp >> 9);
  tmp |= aSideBoard & (tmp >> 9);
  legalBoard |= blankBoard & (tmp >> 9);


  tmp = aSideBoard & (playerBoard >> 7);
  tmp |= aSideBoard & (tmp >> 7);
  tmp |= aSideBoard & (tmp >> 7);
  tmp |= aSideBoard & (tmp >> 7);
  tmp |= aSideBoard & (tmp >> 7);
  tmp |= aSideBoard & (tmp >> 7);
  legalBoard |= blankBoard & (tmp >> 7);


  return legalBoard;
}

void bitboard::swap() {
  ull tmp = playerBoard;
  playerBoard = opponentBoard;
  opponentBoard = tmp;
  player = 1 - player;
}

void bitboard::setBoard(ull _playerBoard, ull _opponentBoard) {
  playerBoard = _playerBoard;
  opponentBoard = _opponentBoard;
}