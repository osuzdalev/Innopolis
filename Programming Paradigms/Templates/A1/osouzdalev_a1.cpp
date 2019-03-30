#include <iostream>

using namespace std;

/*This function template implements the common case
of finding a maximum between two numbers
Actual type for the template instantiation
should have '>' operator defined.*/
template < typename T >
T Max(T a, T b){
	return a > b ? a : b;
}

// creation of C class
class Object{
public:
	int m;
	//adding '>' operator
	Object(): m(0) {}
	bool operator > (Object& object){
		return m > object.m;
	}
	// adding 'cout' function to object
	friend ostream& operator << (ostream& os, const Object& object);
};

ostream& operator << (ostream& os, const Object& object)  
{  
	os << object.m;  
	return os;
}

int main() {
	//template test 1 with type double
	double x, y, result_1;
	x = 1;
	y = 2;
	result_1 = Max(x, y);
	cout << "TEST 1: " << result_1 << endl;
	
	//template test 2 with type int
	int a, b, result_2;
	a = 1;
	b = 2;
	result_2 = Max(a, b);
	cout << "TEST 2: " << result_2 << endl;
	
	//template test 3 with type char
	char c, d, result_3;
	c = 'a';
	d = 'b';
	result_3 = Max(c, d);
	cout << "TEST 3: " << result_3 << endl;
	
	//template test 4 with UDT
	Object object_1, object_2, result_4;
	object_1.m = 1;
	object_2.m = 2;
	result_4 = Max(object_1, object_2);
	cout << "TEST 4: " << result_4 << endl;

	return 0;
}