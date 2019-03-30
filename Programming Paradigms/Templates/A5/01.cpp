#include <iostream>

using namespace std;

//generalising the object
template <typename T, T N>
class bigger{
	public:
		bool operator() (T x) const{
			return x>N;
		}
};

template <typename T, T N>
class lesser{
	public:
		bool operator() (T x) const{
			return x<N;
		}
};

template <typename T, T N>
class is_equal{
	public:
		bool operator() (T x) const{
			return x==N;
		}
};

//generalising the function
template <typename T, typename Comparator>
//1st parameter should allow the following operators:
// '()' '>' '<' '=='
T* find( T* array, int n, Comparator comp){
	T* p = &array[n-1];
	for ( int i= n-1; i>=0; i--){
		if ( comp(*p) ) {
			return p;
		}
		p--; 
	}
	return 0;
}

int main(){
	int A[5] = {0, 1, 0, 2, 0};
	
	int* value_1 = find(A, 5, bigger<int, 1>());
	cout << *value_1 << endl;//desired output: 2
	
	int* value_2 = find(A, 5, lesser<int, 2>());
	cout << *value_2 << endl;//desired output: 0
	
	int* value_3 = find(A, 5, is_equal<int, 2>());
	cout << *value_3 << endl;//desired output: 2
}