/*
In this exercise, you need to write a class that implements a Stack
for generic types. The requirements for the class template are as follows:
  0. This file should not contain main()
  1.  There is a single parameter given to the template as an argument -
      the type of Array
  2. The name of the class should be precisely "Stack"
  3. The current filename should remain "Stack.hpp"
  4. The entire code for the template should be in the current file
  5. The data structure that stores elements of the stack should be
      implemented using Array

The following methods should be implemented to interact with the Stack
object from outside:
1. push(type value)
    Pushes the value into the stack. This method does not return anything.
2. pop()
    Pop the value out of the stack. Returns the reference to the
    latest pushed object
3. numberOfElements()
    Return the integer number of elements currently in the stack.
    When the stack is empty returns 0.
4. empty() return boolean value that indicates whether the
    stack is empty or not
5. You should provide the constructor that can initialize from the existing
    Stack object. Also, create the constructor that
    can initialize using stack size. The default constructor should
    set the stack size to some prespecified value.

!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader and this problem receiving 0 points.
*/
#include "Array.hpp"
#include <iostream>

using namespace std;

template <typename T>
class Stack{
  private:
    int top, size;
    Array<T> S;
  public:
    Stack(int get_size = 5){
      size = get_size;
      S.resize(size);
      top = 0;
    }

    Stack(const Stack &stack){
      top = stack.top;
      for (int i = 0; i <= top; i++){
        S[i] = stack.S[i];
      }
    }

    void push(T val){
      if (top < size){
        S[top] = val;
        top++;
      }
    }

    T& pop(){
      if ( top > 0){
          top--;
      }
      return S[top];
    }

    int numberOfElements(){
      return top;
    }

    bool empty(){
      if (numberOfElements() != 0){
        return false;
      }
      else {
        return true;
      }
    }

    void print(){
      for (int i = 0; i < top; i++){
        cout << S[i] << endl;
      }
    }
};