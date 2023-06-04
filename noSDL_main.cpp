// #include "utils/render.hpp"
#include "agent/aiFactor.hpp"
#include "agent/utils/evaluation.h"
#include "utils/board.hpp"
int main(int argv, char *argc[]) {
  ai *player[2];
  int black, white;
  cout << "黑方 (0: Dai 1: Hua 2: Yu)：";
  cin >> black;
  cout << "白方 (0: Dai 1: Hua 2: Yu)：";
  cin >> white;
  player[0] = aiFactor::createAi(DAI, 0, new normalEvaluation());
  player[1] = aiFactor::createAi(HUA, 1);

  board gameBoard;
  bool end = false;
  int Player = 0;
  while (!end) {
    int move = player[Player]->move(gameBoard.nowBoard);
    Player = !Player;
    if (move == -1) {
      move = player[Player]->move(gameBoard.nowBoard);
      Player = !Player;
      if (move == -1) {
        end = true;
        continue;
      } else {
        gameBoard.move(move);
      }
    } else {
      gameBoard.move(move);
    }
    gameBoard.game();
  }
  return 0;
}
