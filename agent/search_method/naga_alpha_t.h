#include "search_method.h"
#include <unordered_map>
#include <vector>

#define cache_hit_bonus 1000
class nega_alpha_t : public search_method {
public:
  nega_alpha_t() {}
  ull search(bitboard& b);
  int search_nega_alpha_t(bitboard &b, int depth, bool passed, int alpha, int beta);
  inline int calc_move_ordering_value(const bitboard& b);
  const int depth = 12;
  evaluation* e = new normalEvaluation();
  std::unordered_map<bitboard, int , bitboard::hash> former_transpose_table;
  std::unordered_map<bitboard, int , bitboard::hash> transpose_table;
};