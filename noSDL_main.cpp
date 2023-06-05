#include "agent/aiFactor.h"
#include "utils/board.h"

int main(int argv, char *argc[]) {
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
