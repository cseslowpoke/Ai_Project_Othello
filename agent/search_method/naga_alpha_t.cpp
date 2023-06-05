#include "naga_alpha_t.h"


inline int nega_alpha_t::calc_move_ordering_value(const bitboard& b) {
    int res;
    if (former_transpose_table.find(b) != former_transpose_table.end()) {
      res = cache_hit_bonus - former_transpose_table[b];
    } else if (former_transpose_table.find(b) != former_transpose_table.end()) {
      res = cache_hit_bonus - former_transpose_table[b];
    } else {
      res = -e->eval(b);
    }
    return res;
}

ull nega_alpha_t::search(bitboard& b) {
  int alpha, beta, score;
  ull ret;
  ull legalBoard = b.makeLegalBoard(), put;
  std::vector<std::pair<bitboard, ull> > child;
  former_transpose_table.clear();
  transpose_table.clear();
  while(legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    tmp.value = calc_move_ordering_value(tmp);
    child.push_back({tmp, put});
  }

  if(child.size() == 0) {
    return 0;
  }

  for(int i = std::max(1, depth - 3); i <= depth; ++i) {
    alpha = -10000000;
    beta = 10000000;
    if (child.size() >= 2) {
      for (auto &[b, v]: child) {
        b.value = calc_move_ordering_value(b);
      }
    }
    std::sort(child.begin(), child.end(), [](const auto &a, const auto &b) {
      return a.first.value > b.first.value;
    });
    for(auto &[b, v]: child) {
      score = -search_nega_alpha_t(b, i - 1, false, -beta, -alpha);
      if(alpha < score) {
        alpha = score;
        ret = v;
      }
    }
    transpose_table.swap(former_transpose_table);
    transpose_table.clear();
  }
  return ret;
}


int nega_alpha_t::search_nega_alpha_t(bitboard &b, int depth, bool passed, int alpha, int beta) {
  if (depth == 0) {
    return e->eval(b);
  }

  if (transpose_table.find(b) != transpose_table.end()) {
    return transpose_table[b];
  }


  ull legalBoard = b.makeLegalBoard(), put;
  std::vector<bitboard> child;
  while(legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    tmp.value = calc_move_ordering_value(tmp);
    child.push_back(tmp);
  }

  if(child.size() == 0) {
    if (passed) {
      return e->eval(b);
    }
    bitboard tmp = b;
    tmp.swap();
    return -search_nega_alpha_t(tmp, depth, true, -beta, -alpha);
  }

  std::sort(child.begin(), child.end(), [](const bitboard &a, const bitboard &b) {
    return a.value > b.value;
  });

  if(child.size() >= 2) {
    sort(child.begin(), child.end(), [](const bitboard &a, const bitboard &b){
      return a.value > b.value;
    });
  }
  int maxscore = -10000000;
  for(bitboard& b: child) {
    int score = -search_nega_alpha_t(b, depth - 1, false, -beta, -alpha);
    if (score >= beta) {
      return score;
    }
    alpha = std::max(alpha, score);
    maxscore = std::max(maxscore, score);
  }

  transpose_table[b] = maxscore;
  return maxscore;
}
