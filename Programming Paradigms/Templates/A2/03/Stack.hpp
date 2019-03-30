/*
In this exercise, you need to write a class that implements a Stack
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
4. empty() return boolean value that indicates whether the
    stack is empty or not
5. You should provide the constructor that can initialize from the existing
    Stack object

!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader and this problem receiving 0 points.
*/
#include <iostream>

using namespace std;

template <typename T, int size>
class Stack{
  int top;
  T S[size], *p;
  public:
    Stack(){
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
};