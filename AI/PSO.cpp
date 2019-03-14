#include <iostream>
#include <cmath>
#include <map>

#define Def_Num_Solutions 15
#define Num_Particles 5 // Size/dimension of a Solution in terms of # particles

using namespace std;

//function we are attempting to optimize (minimize)
double func1(double* x){
	double total = 0.0;
	for(int i = 0; i<Num_Particles; i++){
		total += pow(x[i], 2);
	}
	return total;
}

double random(double Min, double Max){
	rand();
	return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

//Our "particles" renamed here 'Solutions', they are composed of 5 actual particles each
class Solutions{
	private:
	public:
		double position_i[Num_Particles]; // position of particles
		double velocity_i[Num_Particles]; //particles' velocity
		double pos_best_i[Num_Particles]; //best position individual
		double err_best_i;	//best error individual
		double err_i;
		Solutions(){
			for(int i = 0; i<Num_Particles; i++){
				velocity_i[i] = 0.0;
				position_i[i] = 0.0;
				pos_best_i[i] = 0.0;
			}
		};
		
		Solutions(double initial){
			err_best_i = -1.0;
			err_i = -1.0;	
			
			for(int i = 0; i<Num_Particles; i++){
				velocity_i[i] = random(-1.0, 1.0);
				position_i[i] = initial;
			}
		}
		
		Solutions operator = (Solutions *sol){
			for(int i = 0; i<Num_Particles; i++){
				position_i[i] = sol->position_i[i];
				velocity_i[i] = sol->velocity_i[i];
				pos_best_i[i] = sol->pos_best_i[i];
			}
			err_best_i = sol->err_best_i;
			err_i = sol->err_i;
		}

		void evaluate(double (*costFunc)(double*)){
			//evaluate current fitness
			err_i = costFunc(position_i);
			
			//check to se if the current position is an individual best
			if(err_i < err_best_i || err_best_i == -1.0){
				for(int i = 0; i<Num_Particles; i++){
					pos_best_i[i] = position_i[i];
				}
				err_best_i = err_i;
			}
		}
		
		//update new particle velocity
		void update_velocity(double *pos_best_g, pair<double, double> vel_boundary){
			float w = 1;
			int c1 = 1;
			int c2 = 1;
			
			for(int i = 0; i<Num_Particles; i++){
				double r1 = random(0.0, 1.0);
				double r2 = random(0.0, 1.0);
				
				double vel_cognitive = c1 * r1 * (pos_best_i[i] - position_i[i]);
				double vel_social = c2 * r2 * (pos_best_g[i] - position_i[i]);
				velocity_i[i] = w * velocity_i[i] + vel_cognitive + vel_social;
				
				if(velocity_i[i] < vel_boundary.first){
					velocity_i[i] = vel_boundary.first;
				}
				
				if(velocity_i[i] > vel_boundary.second){
					velocity_i[i] = vel_boundary.second;
				}

			}
		}
		
		//update the particle position based off new velocity updates
		void update_position(pair <double, double> boundaries){
			for(int i = 0; i<Num_Particles; i++){
				position_i[i] = position_i[i] + velocity_i[i];
				
				if(position_i[i] < boundaries.first){
					position_i[i] = boundaries.first;
				}
				
				if(position_i[i] > boundaries.second){
					position_i[i] = boundaries.second;
				}
			}
		}
};

class PSO{
	public:
		double err_best_g;//best global error
		double pos_best_g[Num_Particles];//best global positions
		Solutions * swarm;
		
		PSO(double initial){
			err_best_g = -1.0;
			swarm = new Solutions[Def_Num_Solutions];
			
			//establish the swarm
			for(int i = 0; i<Def_Num_Solutions; i++){
				swarm[i] = new Solutions(initial);
			}
			
		}
		
		//begin optimization loop
		void solver(double (*costFunc)(double*), double initial, pair <double, double> boundaries, pair <double, double> vel_boundary, int max_iter){
			
			int i = 0;
			while(i < max_iter){
				//cycle through particles in swarm and evaluate fitness
				for(int j = 0; j<Def_Num_Solutions; j++){
					swarm[j].evaluate(costFunc);
					
					//determine if current particles is the best globally
					if(swarm[j].err_i < err_best_g || err_best_g == -1){
						for(int k = 0; k<Num_Particles; k++){
							pos_best_g[k] = swarm[j].position_i[k];
						}
						err_best_g = swarm[j].err_i;
					}
				}
				
				//cycle through swarm and update velocities and position
				for(int j = 0; j<Def_Num_Solutions; j++){
						swarm[j].update_velocity(pos_best_g, vel_boundary);
						swarm[j].update_position(boundaries);
				}
				i += 1;
			}
		}
		
		void output(){
			cout << "Final: ";
			for(int i = 0; i<Num_Particles; i++){
				cout << pos_best_g[i] << " ; ";
			}
			cout << endl;
			cout << err_best_g << endl;
		}
};

int main(){
	double initial = 5.0;
	pair <double, double> boundaries = make_pair(-10.0, 10.0);
	pair <double, double> vel_boundary = make_pair(-2.0, 2.0);
	
	PSO a(initial);
	double (*function)(double*);
	function = &func1;
	
	a.solver(function, initial, boundaries,vel_boundary, 100);
	a.output();
	return 0;
}