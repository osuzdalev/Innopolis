/*
In this exercise, you need to write a class that implements Array
for generic types. The requirements for the class template are as follows:
  0. This file should not contain main()
  1. There is a single parameter given to the template as an argument -
      the type of Array
  2. The name of the class should be precisely "Array"
  3. The current filename should remain "Array.hpp"
  4. The entire code for the template should be in the current file

The following methods should be implemented to interact with the Stack
object from outside:
1. Constructor that initializes the Array object. Create constructor that
    can initialize using an array size. The default constructor should
    set the array size to some prespecified value.
2. Destructor for the object. Free the memory allocated for this array.
3. resize(int value) resizes the Array to the size of type*value. The
    reasonable way to resize the array is to allocate new part of memory,
    copy the data, and free the old memory
4. getSize() return the integer number of elements type that the Array
    can store
5. The elements of your Array should be accessible using [], i.e. a[0].
    Overload the operator that is needed for that. Out of boundary check
    should be performed. If the index is out of bounds, throw out_of_range
    exception.

!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader and this problem receiving 0 points.
*/
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Array{
	private:
		T * array;
		int size;
	public:
		Array(int get_size = 5){
			size = get_size;
			array = new T [size];
		}
		~Array(){
			delete[] array;
		}

		T& operator[] (int i) {
			if(i < 0 || i >=size){
				throw out_of_range("ERROR");
			}
			else{
				return array[i];
			}
		}

		void resize(int new_size){
			T *p = new T [new_size];
			for (int i = 0; i< min(size, new_size); i++ ){
				p[i] = array[i];
			}
			delete[] array;

			size = new_size;

			array = new T [size];
			for (int i = 0; i< new_size; i++ ){
				array[i] = p[i];
			}

			delete[] p;
		}

		int getSize(){
			return size;
		}
};