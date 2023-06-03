#include <bits/stdc++.h>
#include "utils/bitboard.hpp"
#include "ai.hpp"
using namespace std;

class min_max_monte_carlo : public ai
{
public:
    min_max_monte_carlo(int _player) : ai(_player) {}
    min_max_monte_carlo(int _player, int _min_max_depth, int _monte_carlo_times) : ai(_player)
    {
        min_max_depth = _min_max_depth;
        monte_carlo_times = _monte_carlo_times;
        srand(time(NULL));
    }
    void name() {
        cout << "hua" << endl;
    }
    int move(std::string board_)
    {
        // cout<<player<<" "<<min_max_depth<<" "<<monte_carlo_times<<endl;
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
        // cout<<black<<" "<<white<<"\n";
        // draw_gb(black,white);
        if (gb.makeLegalBoard() == 0)
            return -1;
        // visit=0;
        chrono::system_clock::time_point start, end;
        start = chrono::system_clock::now();
        pair<int, int> res = minimax(gb, min_max_depth, MX, -INF, INF);
        end = chrono::system_clock::now();
        // cout << (char)('A' + res.first / 8) << (char)('a' + res.first % 8) << "\n";
        //cerr << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "\n";
        // cerr<<visit<<"\n";
        return res.first;
    }
    bool gameOver(bitboard gb)
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

    double heuristic(bitboard gb)
    {
        // return __builtin_popcountll(gb.playerBoard) - __builtin_popcountll(gb.opponentBoard);

        return (double)monte_carlo(gb) / (double)monte_carlo_times;
        // cerr<<score<<"\n";
    }

    void draw_gb(ull black, ull white)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (black & (1ULL << ((i << 3) + j)))
                    cout << "X";
                else if (white & (1ULL << ((i << 3) + j)))
                    cout << "O";
                else
                    cout << "+";
            }
            cout << "\n";
        }
    }
    pair<int, double> minimax(bitboard gb, int depth, int mode, double l_lim, double r_lim)
    {
        // visit++;
        if (depth == 0 || gameOver(gb))
            return make_pair(0, heuristic(gb));
        if (gb.makeLegalBoard() == 0) // passturn
        {
            gb.swap();
            return minimax(gb, depth - 1, 1 - mode, l_lim, r_lim);
        }
        pair<int, double> res, tp;
        if (mode == MX)
            res = make_pair(0, -1);
        else
            res = make_pair(0, 2);
        double res_arr[8][8];
        memset(res_arr, 0, sizeof(res_arr));
        ull legalBoard = gb.makeLegalBoard();

        while (legalBoard > 0)
        {
            int pos = __builtin_ffsll(legalBoard) - 1;
            bitboard nxtgb;
            nxtgb.playerBoard = gb.playerBoard;
            nxtgb.opponentBoard = gb.opponentBoard;
            nxtgb.reverse(1ULL << pos);
            nxtgb.swap();
            tp = minimax(nxtgb, depth - 1, 1 - mode, l_lim, r_lim);
            tp.first = pos;
            res_arr[pos / 8][pos % 8] = tp.second;
            if (mode == MX)
            {
                if (tp.second > res.second)
                    res = tp;
                if (res.second >= r_lim)
                    return res;
                l_lim = max(l_lim, res.second);
            }
            else
            {
                if (tp.second < res.second)
                    res = tp;
                if (res.second <= l_lim)
                    return res;
                r_lim = min(r_lim, res.second);
            }
            legalBoard &= (legalBoard - 1);
        }
        //cerr<<"end__\n";
        return res;
    }

    double monte_carlo(bitboard gb)
    {
        int score = 0;
        for (int i = 0; i < monte_carlo_times; i++)
        {
            score += stimulate(gb);
        }

        return (double)score / (double)monte_carlo_times;
    }
    int stimulate(bitboard gb)
    {
        ull blank_gb;
        int swap_cnt=0;
        while (!gameOver(gb))
        {
            ull legalBoard = gb.makeLegalBoard();
            if (legalBoard == 0)
            {
                gb.swap();
                swap_cnt++;
                continue;
            }
            vector<int> legal_pos;
            int pos;
            while (legalBoard > 0)
            {
                pos = __builtin_ffsll(legalBoard);
                legal_pos.push_back(pos - 1);
                legalBoard &= (legalBoard - 1);
            }
            pos = legal_pos[rand() % legal_pos.size()];
            gb.reverse(1ULL << pos);
            gb.swap();
            swap_cnt++;
        }
        if(swap_cnt&1)
            gb.swap();

        int player_cnt = __builtin_popcountll(gb.playerBoard);
        int oppo_cnt = __builtin_popcountll(gb.opponentBoard);
        int dif = abs(player_cnt - oppo_cnt);
        return (player_cnt > oppo_cnt ? 64 + dif : -(64 + dif));
        // return player_cnt - oppo_cnt;
    }

private:
    int min_max_depth = 5;
    int monte_carlo_times = 100;
    const int BLACK = 0, WHITE = 1;
    const int MX = 0, MN = 1;
    const int INF = 0x3f3f3f3f;
};