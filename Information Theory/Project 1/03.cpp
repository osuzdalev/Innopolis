#include <iostream>

float M = 161.0; //amount of symbols in text file from previous exercise
float N = 3.0; // 3 people in the team

//declaring formulas for each brand
float Orient = M;
float Casio = M + N;
float Swatch = 2 * M;
//calculating total model of watches
float Total = Orient + Casio + Swatch;

using namespace std;

//function computing P(Orient)
float P_Orient(){
	return Orient / Total;
}

//function computing P(Swatch | Orient)
float P_Swatch_if_Orient(){
	float Total_2 = Total - 1.0;
	float c = Swatch / Total_2;
	return c * P_Orient();
}

int main(){
	float c = P_Orient();
	float d = P_Swatch_if_Orient();
	cout << Orient << endl;
	cout << Casio << endl;
	cout << Swatch << endl;
	cout << Total << endl;
	cout << "Probability of Orient watch being picked : "<< c << endl;
	cout << "Probability that Swatch watches were picked second given that Orient watches were picked first : "<< d << endl;
}