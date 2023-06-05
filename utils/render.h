#include "board.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;
// 定義窗口的寬度和高度
class sdl {
public:
  void init();
  void displayBoard(board);
  void choose();
  void quit();
  SDL_Window *window;
  SDL_Renderer *renderer;
};

const int WINDOW_WIDTH = 680;
const int WINDOW_HEIGHT = 680;
// 定義棋盤格的大小和行列數
const int BOARD_SIZE = 8;
const int CELL_SIZE = 80;
// 定義棋盤格的顏色
const SDL_Color COLOR_GREEN = {0, 128, 0, 255};
const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_BROWN = {139, 69, 19, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
// 定義棕色邊框的寬度
const int BORDER_WIDTH = 20;
