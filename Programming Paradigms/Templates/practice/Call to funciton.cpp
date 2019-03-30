#include <iostream>

using namespace std;
//bool (*cond)(int) == "calling value of function 'cond' 
//which takes in an argument of type 'int' and returns a 'bool'"
const int* find2 ( const int* pool, int n, bool (*cond)(int) ) {
	const int* p = pool;
	for ( int i = 0; i<n; i++ ){
		if ( cond(*p) ) return p;  // success
		p++; 
	}
	return 0;  // fail
}

bool condition(int x){
	return x == 2;
}

int main() {
	int A[5] = {0, 1, 0, 2, 0};
	const int* p = find2(A, 5, condition);
	cout << *p;
}