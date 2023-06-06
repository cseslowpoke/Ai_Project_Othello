#include "agent/aiFactor.h"
#include "utils/board.h"

void test2();
int main(int argv, char *argc[]) {
  test2();
  return 0;

  chrono::system_clock::time_point time_start, time_end;
  ai *player[2];
  int black, white;
  cout << "黑方 (0: Dai 1: Hua 2: Yu)：";
  cin >> black;
  player[0] = aiFactor::createAi((aiType)black, 0, 1, 1);
  cout << "白方 (0: Dai 1: Hua 2: Yu)：";
  cin >> white;
  player[1] = aiFactor::createAi((aiType)white, 1, 1, 1);
  cout << "black: ";
  player[0]->name();
  cout << "white: ";
  player[1]->name();
  board gameBoard;
  bool end = false;
  int Player = 0;
  while (!end) {
    time_start = chrono::system_clock::now();
    int move = player[Player]->move(gameBoard.nowBoard);
    time_end = chrono::system_clock::now();
    if (move == -1) {
      Player = !Player;
      time_start = chrono::system_clock::now();
      move = player[Player]->move(gameBoard.nowBoard);
      time_end = chrono::system_clock::now();
      if (move == -1) {
        break;
      } else {
        cout << (Player ? "white " : "black ")<< "time: " << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << '\n';
        gameBoard.move(move);
        Player = !Player;
      }
    } else {
      cout << (Player ? "white " : "black ") << "time: " << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << '\n';
      gameBoard.move(move);
      Player = !Player;
    }
    gameBoard.game();
  }
  return 0;
}



void test() {
  chrono::system_clock::time_point time_start, time_end;
  ai *player[2];
  int black, white;
  player[0] = aiFactor::createAi(DAI, 0, 0, 1);
  player[1] = aiFactor::createAi(DAI, 1, 1, 1);
  cout << "black: ";
  player[0]->name();
  cout << "white: ";
  player[1]->name();
  board gameBoard;
  bool end = false;
  int Player = 0;
  while (!end) {
    time_start = chrono::system_clock::now();
    int move = player[Player]->move(gameBoard.nowBoard);
    time_end = chrono::system_clock::now();
    if (move == -1) {
      Player = !Player;
      time_start = chrono::system_clock::now();
      move = player[Player]->move(gameBoard.nowBoard);
      time_end = chrono::system_clock::now();
      if (move == -1) {
        break;
      } else {
        gameBoard.move(move);
        Player = !Player;
      }
    } else {
      gameBoard.move(move);
      Player = !Player;
    }
  }
  gameBoard.game();
  gameBoard.nowBoard = "---------------------------OX------XO---------------------------";
  gameBoard.change = "----------------------------------------------------------------";
  gameBoard.player = 0;
  swap(player[0], player[1]);
  while (!end) {
    time_start = chrono::system_clock::now();
    int move = player[Player]->move(gameBoard.nowBoard);
    time_end = chrono::system_clock::now();
    if (move == -1) {
      Player = !Player;
      time_start = chrono::system_clock::now();
      move = player[Player]->move(gameBoard.nowBoard);
      time_end = chrono::system_clock::now();
      if (move == -1) {
        break;
      } else {
        gameBoard.move(move);
        Player = !Player;
      }
    } else {
      gameBoard.move(move);
      Player = !Player;
    }
  }
  gameBoard.game();
}

void test2() {
  board gameBoard;
  ai *player[6];
  player[0] = aiFactor::createAi(DAI, 0, 1, 2);
  player[1] = aiFactor::createAi(HUA, 0);
  player[2] = aiFactor::createAi(YU, 0);
  player[3] = aiFactor::createAi(DAI, 1, 1, 2);
  player[4] = aiFactor::createAi(HUA, 1);
  player[5] = aiFactor::createAi(YU, 1);
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if (i == j) continue;
      if(i != 1 && j != 1) {
        continue;
      }
      int p0 = i, p1 = j + 3;
      cout << "black: ";
      player[p0]->name();
      cout << "white: ";
      player[p1]->name();
      gameBoard.nowBoard = "---------------------------OX------XO---------------------------";
      gameBoard.change = "----------------------------------------------------------------";
      gameBoard.player = 0;
      while (true) {
        int move = player[p0]->move(gameBoard.nowBoard);
        if (move == -1) {
          swap(p0, p1);
          move = player[p0]->move(gameBoard.nowBoard);
          if (move == -1) {
            break;
          } else {
            gameBoard.move(move);
            swap(p0, p1);
          }
        } else {
          gameBoard.move(move);
          swap(p0, p1);
        }
      }
      gameBoard.game();
    }
  }
}

void test3() {
  board gameBoard;
  ai *player[8];
  player[0] = aiFactor::createAi(DAI, 0, 0, 0);
  player[1] = aiFactor::createAi(DAI, 0, 0, 1);
  player[2] = aiFactor::createAi(DAI, 0, 0, 2);
  player[3] = aiFactor::createAi(DAI, 0, 0, 3);
  player[4] = aiFactor::createAi(DAI, 1, 0, 0);
  player[5] = aiFactor::createAi(DAI, 1, 0, 1);
  player[6] = aiFactor::createAi(DAI, 1, 0, 2);
  player[7] = aiFactor::createAi(DAI, 0, 0, 3);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if (i == j) continue;
      int p0 = i, p1 = j + 3;
      cout << p0 << ' ' << p1 << '\n';
      cout << "black: ";
      player[p0]->name();
      cout << "white: ";
      player[p1]->name();
      gameBoard.nowBoard = "---------------------------OX------XO---------------------------";
      gameBoard.change = "----------------------------------------------------------------";
      gameBoard.player = 0;
      while (true) {
        int move = player[p0]->move(gameBoard.nowBoard);
        if (move == -1) {
          swap(p0, p1);
          move = player[p0]->move(gameBoard.nowBoard);
          if (move == -1) {
            break;
          } else {
            gameBoard.move(move);
            swap(p0, p1);
          }
        } else {
          gameBoard.move(move);
          swap(p0, p1);
        }
      }
      gameBoard.game();
    }
  }
}
