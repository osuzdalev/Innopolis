#include <iostream>

using namespace std;

template <typename T, typename P>
P find(P first, P beyond, T x){
	P p = first;
	while (p != beyond && *p != x){
		p++;
	}
	return p;
}

int main(){
	int A[5] = {0, 1, 0, 2, 0};
	int* a = find<int, int*>(A, &A[5], 7);
	cout << *a;
}