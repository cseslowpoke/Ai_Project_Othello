
#pragma once
#include "utils/bitBoard.hpp"
#include "ai.hpp"
#include <vector>
#include <ctime>
#include <chrono> 
#include <iostream>
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
       
        chrono::system_clock::time_point start, end;
        start = chrono::system_clock::now();
        if(gb.makeLegalBoard()==0) {
          return -1;
        }
        pair<int, int> res = minimax(gb, min_max_depth, MX, -INF, INF);
        end = chrono::system_clock::now();
        //cout << (char)('A' + res.first / 8) << (char)('a' + res.first % 8) << "\n";
        cout << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "\n";
        return res.first;
    }

    bool gameOver(bitboard gb)
    {
        if(gb.makeLegalBoard() == 0)
        {
            gb.swap();
            if(gb.makeLegalBoard() == 0)
                return true;
            gb.swap();
        }
        return false;
    }

    double heuristic(bitboard gb)
    {
        //return __builtin_popcountll(gb.playerBoard) - __builtin_popcountll(gb.opponentBoard);

       return (double)monte_carlo(gb)/(double)monte_carlo_times;
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
        if (depth == 0 || gameOver(gb))
            return make_pair(0, heuristic(gb));
        if (gb.makeLegalBoard() == 0)   //passturn
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
        ull legalBoard=gb.makeLegalBoard();

        for (int i = 0; i < 64; i++)
        {
            if (legalBoard&(1ULL<<i))
            {
                bitboard nxtgb;
                nxtgb.playerBoard=gb.playerBoard;
                nxtgb.opponentBoard=gb.opponentBoard;
                nxtgb.reverse(1ULL<<i);
                // draw_gb(nxtgb.first,nxtgb.second);
                nxtgb.swap();
                tp = minimax(nxtgb, depth - 1, 1 - mode, l_lim, r_lim);
                tp.first = i;
                res_arr[i / 8][i % 8] = tp.second;
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
            }
        }
        // if (depth == min_max_depth)
        // {
        //     for (int i = 0; i < 8; i++)
        //     {
        //         for (int j = 0; j < 8; j++)
        //             cout << res_arr[i][j] << " ";
        //         cout << "\n";
        //     }
        // }
        return res;
    }
    
    double monte_carlo(bitboard gb)
    {
        // double score=0.0;
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
        while (!gameOver(gb))
        {
            ull legalBoard=gb.makeLegalBoard();
            if(legalBoard==0)
            {
                gb.swap();
                continue;
            }
            vector<int> legal_pos;
            int cnt=0;
            while(legalBoard>0)
            {
                if(legalBoard&1)
                {
                    legal_pos.push_back(cnt);
                }
                legalBoard>>=1;
                cnt++;
            }
            /*vector<ull> legal_pos;
            for(int i=0;i<64;i++)
            {
                if(legalBoard&(1ULL<<i))
                    legal_pos.push_back(1ULL<<i);
            }*/
            int pos = legal_pos[rand() % legal_pos.size()];
            gb.reverse(1ULL<<pos);
            gb.swap();
        }
        // cerr<<"end\n";
        int player_cnt = __builtin_popcountll(gb.playerBoard);
        int oppo_cnt = __builtin_popcountll(gb.opponentBoard);
        //return ((player_cnt >oppo_cnt ? 50 : -50) + player_cnt - oppo_cnt);
        return player_cnt - oppo_cnt;
    }
    /*double uct_search()
    {
        for(int i=0;i<monte_carlo_times;i++)
        {
            Node* leave = selcet();
            double reward = stimulate(leave);
            backup(leave,reward);
            best_child = ucb()
            backup(node,reward);
        }
    }*/
    void name() {
        cout << "hua" << '\n';
    }
private:
    int min_max_depth = 5;
    int monte_carlo_times = 100;
    //pair<int, int> dirr[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    const int BLACK = 0, WHITE = 1;
    const int MX = 0, MN = 1;
    const int INF = 0x3f3f3f3f;
};