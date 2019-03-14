/* !!! IMPORTANT !!!
Structure of the program:
    3 classes
        1) Grid // initiates a grid and places all agents except RRH
        2) Backtracking // all computations for Backtracking
        3) A_Star // all computations for A*
    main function
        100 instances for both algorithmn with outputs
        Both algoritmns use the same grid
        Grid changes every instantiation
*/

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

//class generating a grid with all the elements inside
class Grid{
    const static int DIM = 9 , Zero = 0;
    int R , C;
    //agents
    pair < int , int > granny , wolf , bear;
    //woodcutter house 1 and 2
    pair <int, int > wood1, wood2;
    // woodcutter
    int cutter;
 
    public:
    Grid(){
        generate_grid(DIM , DIM);
    }
    //checking if current cell is inside the grid
    bool in_bound(pair < int , int > P){
        if(P.first < Zero || P.second < Zero || P.first >= R || P.second >= C)
            return 0;
        return 1;
    }
    //checking if current cell is inside wolf detection range
    bool in_wolf_range(pair < int , int > P){
        if(abs(P.first - wolf.first) + abs(P.second - wolf.second) < 2)
            return 1;
        return 0;
    }
    //checking if current cell is inside bear detection range
    bool in_bear_range(pair < int , int > P){
        if(max( abs(P.first - bear.first) , abs(P.second - bear.second) ) < 2 )
            return 1;
        return 0;
    }
    //checking if wood cutter is inside current cell
    bool is_cutter_here(pair < int , int > P){
        if(cutter == Zero && P == wood1)
            return 1;
        if(cutter == 1 && P == wood2)
            return 1;
        return 0;
    }
    void generate_grid(int Rows , int Cols){
        R = Rows;
        C = Cols;
        wolf = { rand() % R , rand() % C };
        bear = { rand() % R , rand() % C };
        //generating granny and woodcutter outside of wolf/bear range
        do{
            granny = {rand() % R , rand() % C};
        }while(in_bear_range(granny) || in_wolf_range(granny));
        do{
            wood1 = {rand() % R , rand() % C};
        }while(in_bear_range(wood1) || in_wolf_range(wood1));
        do{
            wood2 = {rand() % R , rand() % C};
        }while(in_bear_range(wood2) || in_wolf_range(wood2));
        cutter = rand() % 2;
    }
    pair < int , int > grannyplace(){
        return granny;
    }
};

//class where all backtracking computations for solution will be done.
//can be considered as RRH agent.
class Backtracking{
    //creating all actions and state of RRH
    static const int MoveSz = 4 , WolfDetSz = 9 , BearDetSz = 5;
    const pair < int , int > Move[MoveSz] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}};
    const pair < int , int > WolfD[WolfDetSz] = {{0 ,0},{1,0},{2,0},{-1,0},{-2,0},{0,1},{0,2},{0,-1},{0,-2}};
    const pair < int , int > BearD[BearDetSz] = {{0,0},{1,0},{-1,0},{0,1},{0,-1}};
    enum class CellState{SAFE , BEAR , WOLF};
    const static int penalty = 2;

    pair < int , int > girl;
    pair < int , int > wood1 , wood2 , target;
    map < tuple < int , int , int > , bool > mp; //map is a dictionnary (key, value)
    int operations;
    
    //creating a grid to play in
    Grid G;
 
    CellState Detect(pair < int , int > P){
        //detecting Wolf
        for(int i = 0 ; i < WolfDetSz ; i++){
            if(G.in_bound({P.first + WolfD[i].first , P.second + WolfD[i].second})
                && G.in_wolf_range({P.first + WolfD[i].first , P.second + WolfD[i].second}))
                    return CellState::WOLF;
        }

        //detecting Bear
        for(int i = 0 ; i < BearDetSz ; i++){
            if(G.in_bound({P.first + BearD[i].first , P.second + BearD[i].second})
                && G.in_bear_range({P.first + BearD[i].first , P.second + BearD[i].second}))
                    return CellState::BEAR;
        }
        return CellState::SAFE;
    }

    //function computing backtracking algorithm
    bool backtrack(tuple < int , int , int > State){
        int row , col , fruits;
        tie(row , col , fruits) = State;
        //if lost all fruits
        if(fruits == 0) return 0;
        //if at granny with all fuits
        if(G.grannyplace() == make_pair(row , col) && fruits == 6) return 1;
        
        State = make_tuple(row, col, fruits);
        if(mp[State] == true) return 0; // if cell already visited: exit recursion
        mp[State] = true; //otherwise mark as 'already visited'
        
        ++operations;
        bool answer = 0; //checks if there is an answer/possibility to win?
 
        vector < pair < int , int > > WolfPoints , BearPoints;
 
        for(int i = 0 ; i < MoveSz ; i++){
            //making a move
            int newrow = row + Move[i].first , newcol = col + Move[i].second;
            //check if cell in bound
            if(!G.in_bound( {newrow , newcol} )) continue;
            //if cell in bound: check for detection
            CellState type = Detect(make_pair(newrow , newcol));

            if(type == CellState::SAFE){
                if(G.is_cutter_here({newrow , newcol}))
                    answer |= backtrack(make_tuple(newrow , newcol , 6));
                //if everything is ok: continue path through recursion
                else answer |= backtrack(make_tuple(newrow , newcol , fruits));
            }
            else if(type == CellState::BEAR) BearPoints.push_back({newrow , newcol});
            else if(type == CellState::WOLF) WolfPoints.push_back({newrow , newcol});
        }
        //if all Safe cells were visited but granny not found, check around bear
        //go through his detection range if necessary
        for(int i = 0; i < BearPoints.size(); i++){
            int row = BearPoints[i].first , col = BearPoints[i].second;
            if(G.in_wolf_range(make_pair(row , col))) continue;
            if(G.is_cutter_here(make_pair(row , col))) answer |= backtrack(make_tuple(row , col , fruits));
            else if(G.in_bear_range(make_pair(row , col))) answer |= backtrack(make_tuple(row , col , fruits - penalty));
            else answer |= backtrack(make_tuple(row , col , fruits));
        }
        // all Safe+Bear cells visited but granny not found, check around wolf
        for(int i = 0 ; i < WolfPoints.size() ; i++){
            int row = WolfPoints[i].first , col = WolfPoints[i].second;
            if(G.in_wolf_range(make_pair(row , col))) continue;
            if(G.is_cutter_here(make_pair(row , col))) answer |= backtrack(make_tuple(row , col , fruits));
            else if(G.in_bear_range(make_pair(row , col))) answer |= backtrack(make_tuple(row , col , fruits - penalty));
            else answer |= backtrack(make_tuple(row , col , fruits));
        }

        return answer;
    }
    public:
        //constructors
        Backtracking(){}
        Backtracking(Grid gg){
            girl = {0 , 0};
            G = gg;
            target = G.grannyplace();
            operations = 0;
        }
        
        //initializing backtracking
        pair < int , int > solve(){
            if(G.in_wolf_range(girl)) return {0 , operations};
            if(G.in_bear_range(girl)) return { backtrack(make_tuple(0 , 0 , 4)) , operations} ;
            return { backtrack(make_tuple(0 , 0 , 6)) , operations};
        }
};

class A_STAR{
    //creating all actions and state of RRH
    static const int MoveSz = 4 , WolfDetSz = 9 , BearDetSz = 5;
    const pair < int , int > Move[MoveSz] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}};
    const pair < int , int > WolfD[WolfDetSz] = {{0 ,0},{1,0},{2,0},{-1,0},{-2,0},{0,1},{0,2},{0,-1},{0,-2}};
    const pair < int , int > BearD[BearDetSz] = {{0,0},{1,0},{-1,0},{0,1},{0,-1}};
    enum class CellState{SAFE , BEAR , WOLF};
    const static int penalty = 2;
 
    pair < int , int > girl;
    pair < int , int > wood1 , wood2 , target;
 
    int operations;
 
    //creating a grid to play in
    Grid G;
 
    CellState Detect(pair < int , int > P){
        //detecting Wolf
        for(int i = 0 ; i < WolfDetSz ; i++){
            if(G.in_bound({P.first + WolfD[i].first , P.second + WolfD[i].second})
                && G.in_wolf_range({P.first + WolfD[i].first , P.second + WolfD[i].second}))
                    return CellState::WOLF;
        }
 
        //detecting Bear
        for(int i = 0 ; i < BearDetSz ; i++){
            if(G.in_bound({P.first + BearD[i].first , P.second + BearD[i].second})
                && G.in_bear_range({P.first + BearD[i].first , P.second + BearD[i].second}))
                    return CellState::BEAR;
        }
        return CellState::SAFE;
    }
    // tuple representing states
    // < cost , row , column , fruits >
    set < tuple < int ,  int , int , int > > Open;

    map < tuple < int , int , int > , int > BestSoFar;
    // tuple presenting states
    // < row , column , fruits >
    set < tuple < int , int , int > > Close;
 
    //Process the encountered nodes, 
    void relax(int init_cost , int row , int col , int fruits){
        if(fruits <= 0) return;
        tuple < int , int , int  > State = make_tuple(row , col , fruits);
        //check if node has already been processed
        if(Close.count(State) == 1)
            return;
        //discovering a new node
        if(BestSoFar.count(State) == 0){
            BestSoFar[State] = init_cost;
            Open.insert(make_tuple(init_cost , row , col , fruits));
        }
        //replacing best so far with a previously discovered node
        else if(init_cost < BestSoFar[State]){
            Open.erase(make_tuple(BestSoFar[State] , row , col , fruits));
            BestSoFar[State] = init_cost;
            Open.insert(make_tuple(init_cost , row , col , fruits));
        }
    }
    public:
        //constructors
        A_STAR(){}
        A_STAR(Grid gg){
            girl = {0 , 0};
            G = gg;
            target = G.grannyplace();
            operations = 0;
            BestSoFar.clear();
            Open.clear();
            Close.clear();
        }
    
        //initializing A_Star
        pair < int , int > solve(){
            //girl spawns in wolf range
            if(G.in_wolf_range(girl)) return {0 , operations};
            //girl spawns in bear range
            if(G.in_bear_range(girl))
                    Open.insert(make_tuple(0 , girl.first , girl.second , 4));
            else Open.insert(make_tuple(0 , girl.first , girl.second , 6));
    
            while(!Open.empty()){
                int init_cost , row , col , fruits ;
                tie(init_cost , row , col , fruits) = *Open.begin();
                //mark node as closed
                Close.insert(make_tuple(row , col , fruits));
                Open.erase(*Open.begin());
                //winning conditions met
                if(make_pair(row , col) == G.grannyplace()){
                    return {init_cost , operations};
                }
                ++operations;
    
                for(int i = 0 ; i < MoveSz ; i++){
                    //making a move
                    int newrow = row + Move[i].first , newcol = col + Move[i].second;
                    //check if cell in bound
                    if(!G.in_bound( {newrow , newcol} )) continue;
                    //if cell in bound: check for detection
                    CellState type = Detect(make_pair(newrow , newcol));
    
                    if(type == CellState::SAFE){
                        if(G.is_cutter_here({newrow , newcol}))
                            relax(init_cost+1 , newrow , newcol , 6);
                        else relax(init_cost+1 , newrow , newcol , fruits);
                    }
                    //if all Safe cells were visited but granny not found, check around bear
                    //go through his detection range if necessary
                    else if(type == CellState::BEAR){
                        if(G.in_wolf_range(make_pair(row , col))) continue;
                        if(G.is_cutter_here(make_pair(row , col))) relax(init_cost+1 , newrow , newcol , 6);
                        else if(G.in_bear_range(make_pair(row , col))) relax(init_cost+1 , newrow , newcol , fruits - 2);
                        else relax(init_cost+1 , newrow , newcol , fruits);
                    }
                    // all Safe+Bear cells visited but granny not found, check around wolf
                    else if(type == CellState::WOLF){
                        if(G.in_wolf_range(make_pair(row , col))) continue;
                        if(G.is_cutter_here(make_pair(row , col))) relax(init_cost+1 , newrow , newcol , 6);
                        else if(G.in_bear_range(make_pair(row , col))) relax(init_cost+1 , newrow , newcol , fruits - 2);
                        else relax(init_cost+1 , newrow , newcol , fruits);
                    }
                }
            }
        }
};
 
int main(){
    srand(time(NULL));
    std::chrono::time_point<std::chrono::system_clock> t0, t1, t2, t3;
    int dt1, dt2;
    
    for(int j = 0 ; j < 100 ; j++){
        Grid G = Grid();

        Backtracking S1 = Backtracking(G);
        t0 = std::chrono::system_clock::now();
        pair <int, int> a = S1.solve();
        t1 = std::chrono::system_clock::now();
        dt1 = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        
        A_STAR S2 = A_STAR(G);
        t2 = std::chrono::system_clock::now();
        pair <int, int> b = S2.solve();
        t3 = std::chrono::system_clock::now();
        dt2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
        
        cout << "Success = "<< a.first << endl;
        cout << "BACKTRACK : " << " Operations = " <<  a.second<< " Time = " << dt1 << endl;
        cout << "A* : " << " Operations = " << b.first<< " Time = " << dt2 << endl;
        cout << "Steps = " << b.second << endl;
        cout << endl;
    }
}
