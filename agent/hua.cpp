#include "hua.h"


void min_max_monte_carlo::name() {
  cout << "hua" << endl;
}
int min_max_monte_carlo::move(std::string board_){
    bitboard gb;
    char mine, oppo;
    if (player == BLACK)
        mine = 'X', oppo = 'O';
    else
        mine = 'O', oppo = 'X';

    for (int i = 0; i < 64; i++)
    {
        if (board_[i] == mine)
            gb.playerBoard |= (1ULL << i);
        else if (board_[i] == oppo)
            gb.opponentBoard |= (1ULL << i);
    }
    if (gb.makeLegalBoard() == 0)
        return -1;

    pair<int, int> res = minimax(gb, min_max_depth, MX, -INF, INF);
    return res.first;
}

bool min_max_monte_carlo::gameOver(bitboard gb)
{
    if (gb.makeLegalBoard() == 0)
    {
        gb.swap();
        if (gb.makeLegalBoard() == 0)
            return true;
        gb.swap();
    }
    return false;
}

pair<int, int> min_max_monte_carlo::minimax(bitboard gb, int depth, int mode, int l_lim, int r_lim) {
    if (depth == 0 || gameOver(gb)){
        return make_pair(0, monte_carlo(gb));
    }
    if (gb.makeLegalBoard() == 0) { // passturn 
        gb.swap();
        return minimax(gb, depth - 1, 1 - mode, l_lim, r_lim);
    }
    pair<int, int> res, tp;
    if (mode == MX){
        res = make_pair(0, -INF);
    }
    else{
        res = make_pair(0, INF);
    }
    ull legalBoard = gb.makeLegalBoard();
    while (legalBoard > 0) {
        int pos = __builtin_ffsll(legalBoard) - 1;
        bitboard nxtgb;
        nxtgb.playerBoard = gb.playerBoard;
        nxtgb.opponentBoard = gb.opponentBoard;
        nxtgb.reverse(1ULL << pos);
        nxtgb.swap();
        tp = minimax(nxtgb, depth - 1, 1 - mode, l_lim, r_lim);
        tp.first = pos;
        if (mode == MX){
            if (tp.second > res.second){
                res = tp;
            }
        
            if (res.second >= r_lim){
                return res;
            }
            l_lim = max(l_lim, res.second);
        }
        else{
            if (tp.second < res.second){
                res = tp;
            }
            if (res.second <= l_lim){
                return res;
            }
            r_lim = min(r_lim, res.second);
        }
        legalBoard &= (legalBoard - 1);
    }
    return res;
}

int min_max_monte_carlo::monte_carlo(bitboard gb) {
   int score = 0;
    for (int i = 0; i < monte_carlo_times; i++){
        score += stimulate(gb);
    }
    ull corner = 0x8100000000000081;
    int player_corner = __builtin_popcountll(gb.playerBoard & corner);
    int oppo_corner = __builtin_popcountll(gb.opponentBoard & corner);
    //int tp = (player_corner - oppo_corner) * monte_carlo_times*20; 
    if(min_max_depth&1){
        score-=oppo_corner*monte_carlo_times*20;
    }
    else{
        score+=player_corner*monte_carlo_times*20;
    }

    return score;
}

int min_max_monte_carlo::stimulate(bitboard gb) {
  int swap_cnt = 0;
  while (!gameOver(gb)) {
    ull legalBoard = gb.makeLegalBoard();
    if (legalBoard == 0) {
      gb.swap();
      swap_cnt++;
      continue;
    }
    vector<int> legal_pos;
    int pos;
    while (legalBoard > 0) {
      pos = __builtin_ffsll(legalBoard);
      legal_pos.push_back(pos - 1);
      legalBoard &= (legalBoard - 1);
    }
    pos = legal_pos[rand() % legal_pos.size()];
    gb.reverse(1ULL << pos);
    gb.swap();
    swap_cnt++;
  }
  if (swap_cnt & 1) {
    gb.swap();
  }
  int player_cnt = __builtin_popcountll(gb.playerBoard);
  int oppo_cnt = __builtin_popcountll(gb.opponentBoard);
  int dif = abs(player_cnt - oppo_cnt);
  int res=(player_cnt > oppo_cnt ? 64 + dif : -(64 + dif));

  return (min_max_depth&1 ? -res : res);
}