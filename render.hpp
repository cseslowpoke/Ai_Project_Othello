#include <SDL2/SDL.h>
#include <string>
using namespace std;
// 定義窗口的寬度和高度
class sdl{
  public:
    void init();
    void board(string);
    void choose();
    void quit();
    SDL_Window* window;
    SDL_Renderer* renderer;
};

const int WINDOW_WIDTH = 680;
const int WINDOW_HEIGHT = 680;
// 定義棋盤格的大小和行列數
const int BOARD_SIZE = 8;
const int CELL_SIZE = 80;
// 定義棋盤格的顏色
const SDL_Color COLOR_GREEN = { 0, 128, 0, 255 };
const SDL_Color COLOR_BLACK = { 0, 0, 0, 255 };
const SDL_Color COLOR_BROWN = { 139, 69, 19, 255 };
// 定義棕色邊框的寬度
const int BORDER_WIDTH = 20;

void sdl::init(){
  // 初始化SDL
  SDL_Init(SDL_INIT_VIDEO);

  // 創建窗口
  window = SDL_CreateWindow("黑白棋棋盤", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  // 創建渲染器
  renderer = SDL_CreateRenderer(window, -1, 0);
  
}

void sdl::board(string board) {
    // 清空畫面
  SDL_SetRenderDrawColor(renderer, COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b, COLOR_GREEN.a);
  SDL_RenderClear(renderer);

  // 繪製棋盤格
  SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
  for (int row = 0; row < BOARD_SIZE; row++) {
      for (int col = 0; col < BOARD_SIZE; col++) {
          SDL_Rect cellRect = {20+ col * CELL_SIZE,20+ row * CELL_SIZE, CELL_SIZE, CELL_SIZE };
          SDL_RenderDrawRect(renderer, &cellRect);
      }
  }

  // 繪製棕色邊框
  SDL_SetRenderDrawColor(renderer, COLOR_BROWN.r, COLOR_BROWN.g, COLOR_BROWN.b, COLOR_BROWN.a);

  // 上邊框
  SDL_Rect topBorderRect = { 0, 0, WINDOW_WIDTH, BORDER_WIDTH };
  SDL_RenderFillRect(renderer, &topBorderRect);

  // 下邊框
  SDL_Rect bottomBorderRect = { 0, WINDOW_HEIGHT - BORDER_WIDTH, WINDOW_WIDTH, BORDER_WIDTH };
  SDL_RenderFillRect(renderer, &bottomBorderRect);

  // 左邊框
  SDL_Rect leftBorderRect = { 0, 0, BORDER_WIDTH, WINDOW_HEIGHT };
  SDL_RenderFillRect(renderer, &leftBorderRect);

  // 右邊框
  SDL_Rect rightBorderRect = { WINDOW_WIDTH - BORDER_WIDTH, 0, BORDER_WIDTH, WINDOW_HEIGHT };
  SDL_RenderFillRect(renderer, &rightBorderRect);

  // 更新畫面
  SDL_RenderPresent(renderer);
}


void sdl::choose() {
  
}
void sdl::quit() {
    // 釋放資源並關閉SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}