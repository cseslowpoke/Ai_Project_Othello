#include "render.h"
void sdl::init() {
  // 初始化SDL
  SDL_Init(SDL_INIT_VIDEO);

  // 創建窗口
  window = SDL_CreateWindow("黑白棋棋盤", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  // 創建渲染器
  renderer = SDL_CreateRenderer(window, -1, 0);
}

int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
  int offsetx, offsety, d;
  int status;
  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;

  while (offsety >= offsetx) {
    status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
    status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
    status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
    status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
    status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
    status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
    status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
    status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

    if (status < 0) {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return status;
}

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
  int offsetx, offsety, d;
  int status;

  // CHECK_RENDERER_MAGIC(renderer, -1);

  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;

  while (offsety >= offsetx) {

    status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                 x + offsety, y + offsetx);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                 x + offsetx, y + offsety);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                 x + offsetx, y - offsety);
    status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                 x + offsety, y - offsetx);

    if (status < 0) {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return status;
}
void sdl::displayBoard(board gameBoard) {
  // 清空畫面
  SDL_SetRenderDrawColor(renderer, COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b,
                         COLOR_GREEN.a);
  SDL_RenderClear(renderer);

  // 繪製棋盤格
  SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b,
                         COLOR_BLACK.a);
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      SDL_Rect cellRect = {20 + col * CELL_SIZE, 20 + row * CELL_SIZE,
                           CELL_SIZE, CELL_SIZE};
      if (gameBoard.change[row * 8 + col] == '+') {
        SDL_SetRenderDrawColor(renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b,
                               COLOR_RED.a);
        SDL_RenderFillCircle(renderer, 20 + col * CELL_SIZE + CELL_SIZE / 2,
                             20 + row * CELL_SIZE + CELL_SIZE / 2,
                             CELL_SIZE / 2 - 1);
      }
      if (gameBoard.nowBoard[row * 8 + col] == 'X') {
        SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g,
                               COLOR_BLACK.b, COLOR_BLACK.a);
        SDL_RenderFillCircle(renderer, 20 + col * CELL_SIZE + CELL_SIZE / 2,
                             20 + row * CELL_SIZE + CELL_SIZE / 2,
                             CELL_SIZE / 2 - 3);
      } else if (gameBoard.nowBoard[row * 8 + col] == 'O') {
        SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g,
                               COLOR_WHITE.b, COLOR_WHITE.a);
        SDL_RenderFillCircle(renderer, 20 + col * CELL_SIZE + CELL_SIZE / 2,
                             20 + row * CELL_SIZE + CELL_SIZE / 2,
                             CELL_SIZE / 2 - 3);
      }

      SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g,
                             COLOR_BLACK.b, COLOR_BLACK.a);
      SDL_RenderDrawRect(renderer, &cellRect);
    }
  }

  // 繪製棕色邊框
  SDL_SetRenderDrawColor(renderer, COLOR_BROWN.r, COLOR_BROWN.g, COLOR_BROWN.b,
                         COLOR_BROWN.a);

  // 上邊框
  SDL_Rect topBorderRect = {0, 0, WINDOW_WIDTH, BORDER_WIDTH};
  SDL_RenderFillRect(renderer, &topBorderRect);

  // 下邊框
  SDL_Rect bottomBorderRect = {0, WINDOW_HEIGHT - BORDER_WIDTH, WINDOW_WIDTH,
                               BORDER_WIDTH};
  SDL_RenderFillRect(renderer, &bottomBorderRect);

  // 左邊框
  SDL_Rect leftBorderRect = {0, 0, BORDER_WIDTH, WINDOW_HEIGHT};
  SDL_RenderFillRect(renderer, &leftBorderRect);

  // 右邊框
  SDL_Rect rightBorderRect = {WINDOW_WIDTH - BORDER_WIDTH, 0, BORDER_WIDTH,
                              WINDOW_HEIGHT};
  SDL_RenderFillRect(renderer, &rightBorderRect);

  // 更新畫面
  SDL_RenderPresent(renderer);
}

void sdl::choose() {}
void sdl::quit() {
  // 釋放資源並關閉SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}