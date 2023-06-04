#pragma once
#include <bits/stdc++.h>
#include "ai.hpp"
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define SZ 8

//strategy
#define NORMAL 0           //照順序走
#define RANDOM 1           //隨機走
#define CENTER_GREEDY_OUTER_SCORE 2     //內greedy外分數
#define SCORE_TABLE 3      //照分數表
#define MORE_FLIP 4   //這一步可以吃最多棋子


using namespace std;
class CBplayer:public ai{
public:
    CBplayer(int me_);
    CBplayer(int me_,int s,int mr);
    int move(std::string board);
    void name();
    void setMode(int m){mode = m;};
    void setStrategy(int s){strategy = s;};
    void setMR(int mr){MAX_ROUND = mr;};
private:
    int mode = 1;
    int MAX_ROUND  = 9;
    void init();    
    vector<pair<int,int>>normal_table,score_table;
    vector<pair<int,int>> getSearchOrder(const vector<vector<int>> &board);
    int dfs(vector<vector<int>>& check,int me,int who,int round,int nono,int alpha,int beta);
    int me;
    int direction[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    vector<vector<int>>getCheckBoard(const std::string& board);
    int flip(vector<vector<int>>& check,int who,int posX,int posY);
    int getHeuristicScore(vector<vector<int>>& check,int who);
    int ans = -1;
    int strategy = SCORE_TABLE;   //預設策略為該系統測試的最佳策略 可以切換用setStrategy切換 或是建構子傳入
    int table[64] = {1,9,2,4,4,2,9,1,
                     9,10,8,7,7,8,10,9,
                     2,8,3,5,5,3,8,2,
                     4,7,5,inf,inf,5,7,4,
                     4,7,5,inf,inf,5,7,4,
                     2,8,3,5,5,3,8,2,
                     9,10,8,7,7,8,10,9,
                     1,9,2,4,4,2,9,1};
    int posScore_table[8][8] = {{90,-20,10,10,10,10,-20,90},
                             {-20,-20,-5,-5,-5,-5,-20,-20},
                             {10,-5,1,1,1,1,-5,10},
                             {10,-5,1,1,1,1,-5,10},
                             {10,-5,1,1,1,1,-5,10},
                             {10,-5,1,1,1,1,-5,10},
                             {-20,-20,-5,-5,-5,-5,-20,-20},
                             {90,-20,10,10,10,10,-20,90}};
};