/*
In this excersize you need to write a class that implements a List
for generic types. The requirements for the class template are as follows:
  0. This file should not contain main()
  1. There are two parameters given to the template as an argument
  2. The first parameter is the type of List
  3. The second parameter is optional and determines the stack size
  4. The name of the class should be precisely "List"
  5. The current filename should remain "List.hpp"
  6. The entire code for the template should be in the current file

The following methods should be implemented to interact with the Stack
object from outside:
1. Constructor that initializes the List object. This
    constructor does not accept any argument. Memory allocation
    should be perfromed using malloc
2. Destructor for the object. Free allocated memory in this destructor.
3. resize(int value) resizes the List to the size of type*value. The
    resonable way to resize the List is to allocate new part of memory,
    copy the data, and free the old memory
4. getSize() return the integer number of elements type that the List
    can store
5. The elements of your List should be accessible using [], i.e. a[0].
    Overload the operator that is needed for that. Out of boundary check
    should be performed. If the index is out of bounds, throw out_of_range
    exception.
6. Do not use any libraries other than ones listed below

!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader, and this excersize will receive 0 score.
*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template <typename T, unsigned N = 5>
class List{
  private:
    T * list;
    int size;
  public:
    List(){
      size = N;
      list = (T*) malloc(sizeof(T) * size);
    }
    ~List(){
      delete[] list;
    }

    T& operator[] (int i) {
      if(i < 0 || i >= size){
        throw out_of_range("o.souzdalev");
      }
      else{
        return list[i];
      }
    }

    void resize(int new_size){
      T *p = new T [new_size];
      for (int i = 0; i< min(size, new_size); i++ ){
        p[i] = list[i];
      }
      delete[] list;

      size = new_size;

      list = new T [size];
      for (int i = 0; i< new_size; i++ ){
        list[i] = p[i];
      }
      
      delete[] p;
    }

    int getSize(){
      return size;
    }

    void print(){
      for (int i = 0; i<size; i++){
        cout << list[i] << " ";
      }
      cout << endl;
    }
};