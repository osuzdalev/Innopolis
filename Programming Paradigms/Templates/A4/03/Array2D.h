/*
Write an implementation of class Array2D that uses the idea of the class Range to
allow for arbitrary indexing ranges. The template for class Array2D should accept
the following parameters:
1. Type of objects in Array2D
2. Lower bound for the index, i.e. the minimum valid value of index of the
    first dimension
3. Upper bound for the index, i.e. the maximum valid value of index of the
    first dimension
4. Lower bound for the index, i.e. the minimum valid value of index of the
    second dimension
5. Upper bound for the index, i.e. the maximum valid value of index of the
    second dimension

The values of upper and lower bounds are assumed to be valid and no
additional checks are required.

Similarly to the problem 2, you need to overload the operator []. The overloading
process is different. Look for information on how to implement multidimensional
arrays in C++. Should any of indexes be out of boundary, throw the
std::runtime_error exception.

Additional methods to be implemented:
1. size() returns the total number of elements in the Array2D
2. getLB() returns the pointer to the array of lower bounds for each dimension
3. getUB() returns the pointer to the array of upper bounds for each dimension

For testing purposes try:
  Array<int,-5,5,0,10> a;
  a[-4][2] = 48;
*/
#include <iostream>

using namespace std;
template <typename T, T LB, T RB, T LB2, T RB2>
class ArrayOfArrays{
	private:
		class Array{
			private:
				T* array;
			public:
				Array(){
					array = new T[RB2 - LB2 + 1];		
				}

				T &operator[](int j) {
					if(j < LB2 || j > RB2){
						throw runtime_error("index out of range");
					}
					return array[j - LB2];
				}
		};
		
		Array* arrayofarrays;
	public:
		ArrayOfArrays() {
			arrayofarrays = new Array[RB - LB + 1];
		}
		
		Array &operator[](int i) {
			if(i < LB || i > RB){
				throw runtime_error("index out of range");
			}
			return arrayofarrays[i - LB];
		}

		int size(){
			return (RB - LB + 1) * (RB2 - LB2 + 1);
		}
		T* getLB(){
			T lb[2] = {LB, LB2};
			return lb;
		}
		T* getRB(){
			T rb[2] = {RB, RB2};
			return rb;
		}
};