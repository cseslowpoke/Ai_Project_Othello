#include "dai.h"
#define cache_hit_bonus 1000  
int vis = 0;
void dai::name() {
  std::cout << "dai2" << std::endl;
}
int dai::move(std::string checker) {
  vis = 0;
  transpose_table_upper.clear();
  transpose_table_lower.clear();
  former_transpose_table_upper.clear();
  former_transpose_table_lower.clear();
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
  ull put = nat_search(b);
  end = std::chrono::system_clock::now();
  // std::cout << "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
  // std::cout << "vis:" << vis << '\n';
  for (int i = 0; i < 64; i++) {
    if (put & (1ULL << i)) {
      std::cout << i << '\n';
      return i;
    }
  }
  return -1;
}

inline int dai::calc_move_ordering_value(const bitboard b) {
    int res;
    if (former_transpose_table_upper.find(b) != former_transpose_table_upper.end()) {
        // 前回の探索で上限値が格納されていた場合
        res = cache_hit_bonus - former_transpose_table_upper[b];
    } else if (former_transpose_table_lower.find(b) != former_transpose_table_lower.end()) {
        // 前回の探索で下限値が格納されていた場合
        res = cache_hit_bonus - former_transpose_table_lower[b];
    } else {
        // 前回の探索で枝刈りされた
        res = -e->eval(b);
    }
    return res;
}


ull dai::na_search(bitboard& b) {
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  ull maxput = 0;
  while (legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    int score = -nega_alpha(tmp, depth - 1, false, -10000000, 10000000);
    if (score > maxscore) {
      maxscore = score;
      maxput = put;
    }
  }
  return maxput;
}
int dai::nega_alpha(bitboard &b, int depth, bool passed, int alpha, int beta) {
  vis++;
  if (depth == 0) {
    return e->eval(b);
  }
  ull legalBoard = b.makeLegalBoard(), put;
  int maxscore = -10000000;
  while (legalBoard != 0) {
    put = legalBoard & (-legalBoard);
    legalBoard ^= put;
    bitboard tmp = b;
    tmp.reverse(put);
    tmp.swap();
    int score = -nega_alpha(tmp, depth - 1, false, -beta, -alpha);
    if (score >= beta) {
      return beta;
    }
    alpha = std::max(alpha, score);
    maxscore = std::max(maxscore, score);
  }

  if (maxscore == -10000000) {
    if (passed) {
      return e->eval(b);
    }
    bitboard tmp = b;
    tmp.swap();
    return -nega_alpha(tmp, depth, true, -beta, -alpha);
  }
  return maxscore;
}


ull dai::nat_search(bitboard& b) {
  int alpha, beta, score;
  ull ret;
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
    return 0;
  }

  for(int i = std::max(1, depth - 3); i <= depth; ++i) {
    alpha = -10000000;
    beta = 10000000;
    if (child.size() >= 2) {
      for (bitboard &b: child) {
        b.value = calc_move_ordering_value(b);
      }
    }
    std::sort(child.begin(), child.end(), [](const bitboard &a, const bitboard &b) {
      return a.value > b.value;
    });
    for(bitboard& b: child) {
      score = -nega_alpha_transpose(b, i - 1, false, -beta, -alpha);
      if(alpha < score) {
        alpha = score;
        ret = b.policy;
      }
    }
    transpose_table_upper.swap(former_transpose_table_upper);
  }
  return ret;
}
int dai::nega_alpha_transpose(bitboard &b, int depth, bool passed, int alpha, int beta) {
  vis++;
  if (depth == 0) {
    return e->eval(b);
  }

  if (transpose_table_upper.find(b) != transpose_table_upper.end()) {
    return transpose_table_upper[b];
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
    return -nega_alpha_transpose(tmp, depth, true, -beta, -alpha);
  }

  std::sort(child.begin(), child.end(), [](const bitboard &a, const bitboard &b) {
    return a.value > b.value;
  });

  int maxscore = -10000000;
  for(bitboard& b: child) {
    int score = -nega_alpha_transpose(b, depth - 1, false, -beta, -alpha);
    if (score >= beta) {
      return beta;
    }
    alpha = std::max(alpha, score);
    maxscore = std::max(maxscore, score);
  }

  transpose_table_upper[b] = maxscore;
  return maxscore;
}

int dai::nega_scout(bitboard &b, int depth, bool passed, int alpha, int beta) {
  if (depth == 0) {
    return e->eval(b);
  }

  int u = -10000000,l = 10000000;
  if (former_transpose_table_upper.find(b) != former_transpose_table_upper.end()) {
    u = former_transpose_table_upper[b];
  }
  if (former_transpose_table_lower.find(b) != former_transpose_table_lower.end()) {
    l = former_transpose_table_lower[b];
  }
  if (u == l) {
    return u;
  }
  alpha = std::max(alpha, u);
  beta = std::min(beta, l);
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
  
}