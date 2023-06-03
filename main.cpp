#include "utils/render.hpp"
#include "utils/board.hpp"
#include "agent/aiFactor.hpp"
int main(int argv, char* argc[]) {
  ai* player[2];

  cout << "黑方： 0: Dai 1: Hua 2: Yu：";
  int black;
  cin >> black;
  cout << "白方： 0: Dai 1: Hua 2: Yu：";
  int white;
  cin >> white;
  player[0] = aiFactor::createAi(DAI, 0);
  player[1] = aiFactor::createAi(HUA, 1);
  player[0]->name();
  player[1]->name();
  sdl r;
  r.init();

  board gameBoard;
  bool quit = false, end = false;
  int Player = 0;
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
            int move = player[Player]->move(gameBoard.nowBoard);
            cout << move << endl;
            Player = !Player;
            if (move == -1) {
              move = player[Player]->move(gameBoard.nowBoard);
              Player = !Player;
              if (move == -1) {
                end = true;
                break;
              }
              else {
                gameBoard.move(move);
              }
              continue;
            }
            else {
              gameBoard.move(move);
            }
          }
          break;
      }
    }
    r.displayBoard(gameBoard);
  }

  r.quit();
  gameBoard.result();
  return 0;
}
