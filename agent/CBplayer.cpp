#include "CBplayer.h"
int CBplayer::getHeuristicScore(vector<vector<int>> &check, int who)
{
    int rt = 0;
    for(int i=0;i<SZ;i++){
        for(int j=0;j<SZ;j++){
            if(check[i][j] == who)
                rt++;
            else if(check[i][j] == (who^1))
                rt--;
        }
    }   
    if(mode == 1){
        for(int i=0;i<SZ;i++){
            for(int j=0;j<SZ;j++){
                if(check[i][j] == who)
                    rt+=posScore_table[i][j];
                else if(check[i][j] == (who^1))
                    rt-=posScore_table[i][j];
            }
        }  
    }
    return rt;
}
CBplayer::CBplayer(int me_):ai(me_){
    me = me_;
    init();
}

CBplayer::CBplayer(int me_,int s,int mr):ai(me_){
    me = me_;
    strategy = s;
    init();
    MAX_ROUND = mr;
}

void CBplayer::name() {
    cout << "YU\n";
}

void CBplayer::init(){
    for(int i=0;i<SZ;i++){
        for(int j=0;j<SZ;j++){
            normal_table.push_back({i,j});
        }
    }
    
    for(int i=1;i<11;i++){
        for(int j=0;j<64;j++){
            if(table[j] == i){
                score_table.push_back({j/8,j%8});
            }
        }
    }
}

int CBplayer::move(std::string board)
{
    ans = -1;
    vector<vector<int>> check = getCheckBoard(board);
    int alpha = -inf,beta = inf;

    int rt = dfs(check,me,me,0,0,alpha,beta);
    //cout << ans << "\n";
    return ans;
}

vector< pair<int,int> > CBplayer::getSearchOrder(const vector<vector<int>> & board){

    vector<pair<int,int>> rt;
    if(strategy == NORMAL){
        rt = normal_table;
    }
    if(strategy == RANDOM){
        rt = normal_table;
        random_shuffle(rt.begin(),rt.end());
    }       
    if(strategy == SCORE_TABLE){
        rt = score_table;
    }
    if(strategy == CENTER_GREEDY_OUTER_SCORE){
        rt.clear();
        for(int i = 1; i <= 3; i++){
            for(int j=0;j<64;j++){
                if(table[j] == i){
                    rt.push_back({j/8,j%8});
                }
            }
        }
        map<int, vector<pair<int, int>>, greater<int>> mp;
        for(int i = 0; i < SZ; i++){
            for(int j = 0; j < SZ; j++){
                if(board[i][j] == -1 && !((i<=2&&j<=2)||(i<=2&&j>=5)||(i>=5&&j<=2)||(i>=5&&j>=5))){
                    vector<vector<int>> tmpBoard = board;
                    int score = flip(tmpBoard, me, i, j);
                    mp[score].push_back(make_pair(i, j));
                }
            }
        }
        for(auto i : mp){
            for(auto j : i.second){
                rt.push_back(j);
            }
        }
        for(int i = 8; i <= 10; i++){
            for(int j=0;j<64;j++){
                if(table[j] == i){
                    rt.push_back({j/8,j%8});
                }
            }
        }
    }
    if(strategy == MORE_FLIP){
        map<int, vector<pair<int, int>>, greater<int>> mp;
        for(int i = 0; i < SZ; i++){
            for(int j = 0; j < SZ; j++){
                if(board[i][j] == -1){
                    vector<vector<int>> tmpBoard = board;
                    int score = flip(tmpBoard, me, i, j);
                    mp[score].push_back(make_pair(i, j));
                }
            }
        }
        rt.clear();
        for(auto i : mp){
            for(auto j : i.second){
                rt.push_back(j);
            }
        }
    }
    return rt;
} 
int CBplayer::dfs(vector<vector<int>>& check,int me,int who,int round,int nono,int alpha,int beta) {
    if(round == MAX_ROUND){
        //cout << MAX_ROUND << "\n";
        return getHeuristicScore(check,me);
    }
    int val;

    if(me == who) val = -inf;
    else val = inf;

    bool cango = 0;

    vector<pair<int,int>> order = getSearchOrder(check);

    for(int k=0;k<order.size();k++){
        int i = order[k].first, j = order[k].second;
        
        vector<vector<int>> dulCheck = check;
        
        if(flip(dulCheck,who,i,j) != 0){
            cango = 1;           

            int tpval = dfs(dulCheck,me,who^1,round+1,0,alpha,beta);
            //cout << tpval << "\n";
            if(round == 0){
                if(tpval > val) ans = (i*SZ+j);
                else if(tpval == val && (rand()&1)) ans = (i*SZ+j);
            }
            if(me == who) {
                val = max(val,tpval);
                if(val >= beta) {
                    return val;   //目前最大的val比beta大 那就不用跑了
                }
                alpha = max(alpha,val);
            }
            else {
                val = min(val,tpval);
                if(val <= alpha) {
                    return val;
                }
                beta = min(val,beta);
            }
        }
    }

    if(cango == 0){ //同一個人連續動
        if(nono == 1) return getHeuristicScore(check,me);
        else {
            vector<vector<int>> dulCheck = check;
            return dfs(dulCheck,me,who^1,round+1,1,alpha,beta);
        }
        
    }
    return val;
    return 0;
}

vector<vector<int>>CBplayer::getCheckBoard(const std::string &board)
{
    vector<vector<int>> check(SZ,vector<int>(SZ,-1));
    for(int i=0;i<SZ;i++){
        for(int j=0;j<SZ;j++){
            char c = board[i*SZ+j];
            if(c == 'X'){
                check[i][j] = 0;  //player0: dark
            }else if(c == 'O'){
                check[i][j] = 1;  //player1: light
            }
        }
    }
    return check;
}

int CBplayer::flip(vector<vector<int>>& check,int who,int posX,int posY){
    int rt = 0,tprt;
    int tpX,tpY;
    if(check[posX][posY] != -1) return 0; 
    for(int dir=0;dir<8;dir++){
        tprt = 0;
        tpX = posX + direction[dir][0];
        tpY = posY + direction[dir][1];
        while(tpX >= 0 && tpX < SZ && tpY >= 0 && tpY < SZ&& check[tpX][tpY] == (who^1)){
            tprt++;
            tpX += direction[dir][0];
            tpY += direction[dir][1];
        }
        if(!(tpX >= 0 && tpX < SZ && tpY >= 0 && tpY < SZ)) {
            tprt = 0;
            continue;
        }
        if(check[tpX][tpY] == who) { //合法
            tpX -= direction[dir][0];
            tpY -= direction[dir][1];            
            while(tpX >= 0 && tpX < SZ && tpY >= 0 && tpY < SZ && check[tpX][tpY] == (who^1)){
                check[tpX][tpY] = who;
                tpX -= direction[dir][0];
                tpY -= direction[dir][1];
            }            
        }else tprt = 0;
        rt += tprt;
    }
    if(rt) check[posX][posY] = who;
    return rt;
}