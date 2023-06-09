#include "ai.h"
#include "utils/bitboard.h"
#include <bits/stdc++.h>
using namespace std;

class min_max_monte_carlo : public ai {
public:
    min_max_monte_carlo(int _player) : ai(_player) {}
    min_max_monte_carlo(int _player, int _min_max_depth, int _monte_carlo_times) : ai(_player)
    {
        min_max_depth = _min_max_depth;
        monte_carlo_times = _monte_carlo_times;
        srand(time(NULL));
    }

    void name();
    int move(std::string board_);
    bool gameOver(bitboard gb);
    pair<int, int> minimax(bitboard gb, int depth, int mode, int l_lim, int r_lim);
    int monte_carlo(bitboard gb);
    int stimulate(bitboard gb);

private:
    int min_max_depth = 5;
    int monte_carlo_times = 100;
    const int BLACK = 0, WHITE = 1;
    const int MX = 0, MN = 1;
    const int INF = 0x3f3f3f3f;
};