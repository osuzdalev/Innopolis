/*
Come up with several examples of using Array2D template. Demonstrate the use of
the functionality. Provide readable output.
*/
#include "Array2D.h"

int main(){
	ArrayOfArrays<int,-5,5,0,10> a;
	a[-4][2] = 48;

	std::cout << a[-4][2];
}