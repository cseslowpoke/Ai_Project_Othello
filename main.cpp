#include "agent/aiFactor.h"
#include "utils/board.h"
#include "utils/render.h"
#include <chrono>
int main(int argv, char *argc[]) {
  chrono::system_clock::time_point start, end;
  ai *player[2];
  int black, white;
  cout << "黑方 (0: Dai 1: Hua 2: Yu)：";
  cin >> black;
  player[0] = aiFactor::createAi((aiType)black, 0, 0);
  cout << "白方 (0: Dai 1: Hua 2: Yu)：";
  cin >> white;
  player[1] = aiFactor::createAi((aiType)white, 1, 1);
  cout << "black: ";
  player[0]->name();
  cout << "white: ";
  player[1]->name();

  sdl r;
  board gameBoard;
  bool quit = false;
  int Player = 0;

  r.init();
  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }
    start = chrono::system_clock::now();
    int move = player[Player]->move(gameBoard.nowBoard);
    end = chrono::system_clock::now();
    if (move == -1) {
      Player = !Player;
      start = chrono::system_clock::now();
      move = player[Player]->move(gameBoard.nowBoard);
      end = chrono::system_clock::now();
      if (move == -1) {
        break;
      } else {
        cout << (Player ? "white " : "black ")<< "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';
        gameBoard.move(move);
        Player = !Player;
      }
    } else {
      cout << (Player ? "white " : "black ") << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << '\n';
      gameBoard.move(move);
      Player = !Player;
    }
    r.displayBoard(gameBoard);
  }
  while(!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }
  }
  r.quit();
  gameBoard.result();
  return 0;
}
