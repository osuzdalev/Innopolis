/*
Come up with several examples of using Range template. Demonstrate the use of
the functionality. Provide readable output.
*/
#include "Range.h"
int main(){
	Range<int, -5, 5> a(0);
	Range<int, -5, 5> b(0);
	Range<int, -5, 5> c(0);

	int a_Val = a.getval();
	//increment a
	a++;
	a_Val = a.getval();
	cout << "a =  "<< a_Val << endl;
	//decrement a
	a--;
	a_Val = a.getval();
	cout << "a =  "<< a_Val << endl;
	
	//Casting
	b = (long)b;

	return 0;
}
