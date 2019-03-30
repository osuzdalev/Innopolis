/*
Come up with several examples of using Array template. Demonstrate the use of
the functionality. Provide readable output.
*/
#include "Array.h"

int main(){
	Array<int, -1, 1> a;
	a[-1] = 2;
	
	int b = a[-1];
	cout << "a[-1] " << b<< endl;
	
	int LB = a.getLB();
	cout << "LB " << LB<< endl;
	int RB = a.getRB();
	cout << "RB " << RB<< endl;
}