#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Grid{
	private:
		const static int DIM = 5, Zero = 0, BLOCKS = 4;
		int R, C;
		pair <int, int> blocks[BLOCKS] = {{1, 1}, {3, 1}, {3, 2}, {3, 3}}, smiley = {4, 3};
	public:
		Grid(){
			generate_grid(DIM, DIM);
		}
		void generate_grid(int Rows, int Cols){
			R = Rows;
			C = Cols;
		}
		
		bool in_bound(pair <int, int> P){
			if(P.first < Zero || P.second < Zero || P.first >= R || P.second >= C)
				return 0;
			return 1;
		}
		bool blocked(pair <int, int> P){
			for(int i = 0; i<BLOCKS; i++){
				if(P.first == blocks[i].first && P.second == blocks[i].second)
					return 1;
			}
			return 0;
		}
		pair <int, int> smileyplace(){
			return smiley;
		}
		void output(){
			for(int j = 0 ; j < R ; j++){
				for(int i = 0 ; i < C ; i++){
					if(j + i == 0) cout<<'T';
					else if(make_pair(j , i) == blocks[0] || make_pair(j , i) == blocks[1] || make_pair(j , i) == blocks[2] || make_pair(j , i) == blocks[3]) cout<<'X';
					else if(make_pair(j , i) == smiley) cout<<'S';
					else  cout<<'.';
				}
			puts("");
			}
		}
};

class BreadthFS{
	private:
		static const int MoveSz = 8;
		const pair <int, int> Move[MoveSz] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}, {1 , 1}, {-1 , 1}, {-1 , -1}, {1 , -1}};
		enum class CellState{SAFE, BLOCKED};
		
		pair <int, int> tank, target;
		int operations;
		
		Grid G;
		
		CellState Detect(pair <int, int> P){
			if(G.in_bound(P) && G.blocked(P)){
				return CellState::BLOCKED;
			}
			else{
			return CellState::SAFE;
			}
		}
		
		set <tuple <int, int, int> > Open;
		
		map <tuple <int, int>, int> BestSoFar;
		set <tuple <int, int> > Close;
		
		void relax(int init_cost, int row, int col){
			tuple <int, int> State = make_tuple(row, col);
			if(Close.count(State) == 1)
				return;
			if(BestSoFar.count(State) == 0){
				BestSoFar[State] = init_cost;
				Open.insert(make_tuple(init_cost, row, col));
			}
			else if(init_cost < BestSoFar[State]){
				Open.erase(make_tuple(BestSoFar[State], row, col));
				BestSoFar[State] = init_cost;
				Open.insert(make_tuple(init_cost, row, col));
			}
		}
	public:
		BreadthFS(){}
		BreadthFS(Grid gg){
			tank = {0, 0};
			G = gg;
			target = G.smileyplace();
			operations = 0;
			BestSoFar.clear();
			Open.clear();
			Close.clear();
		}
		
		pair <int, int> BFS(){
			Open.insert(make_tuple(0, tank.first, tank.second));
			
			while(!Open.empty()){
				int init_cost, row, col;
				tie(init_cost, row, col) = *Open.begin();
				Close.insert(make_tuple(row, col));
				Open.erase(*Open.begin());
				if(make_pair(row, col) == G.smileyplace()){
					return {init_cost, operations};
				}
				++operations;
				
				for(int i = 0; i<MoveSz; i++){
					int newrow = row + Move[i].first, newcol = col + Move[i].second;
					if(!G.in_bound({newrow, newcol})) {
						continue;
					}	
					CellState type = Detect(make_pair(newrow, newcol));
					
					if(type == CellState::SAFE){
						relax(init_cost+1, newrow, newcol);
					}
					else if(type == CellState::BLOCKED){
						continue;
					}
				}
			}
		}
};

int main() {
	Grid G = Grid();
		
	BreadthFS S = BreadthFS(G);
	pair <int, int> a = S.BFS();
	G.output();
	cout << a.first << ' ' << a.second<< endl;
}