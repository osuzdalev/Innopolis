/*
In this exercice, you need to write a class that implements a Stack
for generic types. The requirements for the class template are as follows:
  0. This file should not contain main()
  1. There are two parameters given to the template as an argument
  2. The first parameter is the type of Stack
  3. The second parameter is optional and determines the stack size
  4. The name of the class should be precisely "Stack"
  5. The current filename should remain "Stack.hpp"
  6. The entire code for the template should be in the current file

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

!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader and this problem receiving 0 points.
*/
#include <iostream>

using namespace std;

template <typename T, int size>
class Stack{
  int top;
  T S[size];
  public:
    Stack(){
      top = 0;
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
};