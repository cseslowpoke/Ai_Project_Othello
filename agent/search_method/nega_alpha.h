#include "search_method.h"

class nega_alpha : public search_method{
public:
  nega_alpha(): search_method() {}
  nega_alpha(int eval): search_method(eval) {}
  ull search(bitboard& b);
  int search_nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta);
  const int depth = 10;
  evaluation* e = new normal_eval_a();
};