#include "dai.h"
void dai::name() {
  std::cout << "dai2" << std::endl;
}
int dai::move(std::string checker) {
  ull black = 0, white = 0;
  bitboard b;
  for (int i = 0; i < 64; i++) {
    if (checker[i] == 'X') {
      black |= (1ULL << i);
    } else if (checker[i] == 'O') {
      white |= (1ULL << i);
    }
  }
  if (player == 1) {
    b.setBoard(white, black);
  } else {
    b.setBoard(black, white);
  }
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();
  ull put = search->search(b);
  end = std::chrono::system_clock::now();
  std::cout << "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
  return __builtin_ffsll(put) - 1;
}