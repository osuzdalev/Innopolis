#include <iostream>

using namespace std;

// generalising both the object and the function

template <typename T, T N>
class bigger{
	public:
		bool operator()(T x) const{
			return x>N;
		}	
};

template <typename T, typename Comparator>
T* find(T* pool, int n, Comparator comp){
	T* p = pool;
	for (int i = 0; i<n; i++){
		if (comp(*p)){
			return p; //success
		}
		p++;
	}
	return 0;
}

int main() {
	int A[5] = {0, 1, 0, 2, 0};
	int* p = find(A, 5, bigger<int, 1>());
	cout << *p;
	
}