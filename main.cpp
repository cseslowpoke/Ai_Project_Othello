#include "utils/render.hpp"
#include "utils/board.hpp"
#include "agent/aiFactor.hpp"
#include "agent/utils/evaluation.hpp"
int main(int argv, char* argc[]) {
  ai* player[2];
  int isGui = 0;
  int black, white;
  cout << "(0) cui (1) gui：";
  cin >> isGui;
  cout << "黑方 (0: Dai 1: Hua 2: Yu)：";
  cin >> black;
  cout << "白方 (0: Dai 1: Hua 2: Yu)：";
  cin >> white;
  player[0] = aiFactor::createAi(DAI, 0, new normalEvaluation());
  player[1] = aiFactor::createAi(HUA, 1);

  

  sdl r;
  // r.init();

  board gameBoard;
  bool quit = false, end = false;
  int Player = 0;

  if (isGui) {
    r.init();
    while(!quit) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            quit = true;
            break;
          case SDL_KEYDOWN:
            if (end == true) {
              continue;
            }
            if (event.key.keysym.sym == SDLK_RETURN) {
              
            }
            break;
        }
      }
      int move = player[Player]->move(gameBoard.nowBoard);
      Player = !Player;
      if (move == -1) {
        move = player[Player]->move(gameBoard.nowBoard);
        Player = !Player;
        if (move == -1) {
          end = true;
          continue;
        }
        else {
          gameBoard.move(move);
        }
      }
      else {
        gameBoard.move(move);
      }
      r.displayBoard(gameBoard);
    }
    r.quit();
  }
  else {

  }
  gameBoard.result();
  return 0;
}
