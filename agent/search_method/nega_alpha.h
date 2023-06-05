#include "search_method.h"

class nega_alpha : public search_method{
public:
  nega_alpha(){}
  ull search(bitboard& b);
  int search_nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta);
  const int depth = 10;
  evaluation* e = new normalEvaluation();
};