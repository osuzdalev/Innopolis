/*
In this excersize you need to write a class that implements a Stack
for generic types. The requirements for the class template are as follows:
  0. This file should not contain main()
  1. There are two parameters given to the template as an argument
  2. The first parameter is the type of Stack
  3. The second parameter determines the container for the stack. The
      second parameter is the template of the corresponding container. In
      your problem that will be either Array or List
  4. The name of the class should be precisely "Stack"
  5. The current filename should remain "Stack.hpp"
  6. The entire code for the template should be in the current file
  7. The data structure that stores elements of the stack should be
      implemented using Array

The following methods should be implemented to interact with the Stack
object from outside:
1. push(type value)
    Pushes the value into the stack. This method does not return anything.
2. pop()
    Pop the value out of stack. Returns the reference to the
    latest pushed object
3. numberOfElements()
    Return the integer number of elements currently in the stack.
    When the stack is empty returns 0.
4. empty() return boolean value that indicates whether the
    stack is empty or not
5. You should provide the constructor that can initialize from the existing
    Stack object
6. Do not use any libraries other than ones listed below

We may test your implementation using funcitons such as:
  Stack<int,Array> a;
  Stack<int,List> b;


!!!!IMPORTANT!!!!
Failure to follow any of these requirements will lead to the
compilation failure by the grader, and this excersize will receive 0 score.
*/

#include <iostream>


using namespace std;

template <typename T, template<typename, unsigned N = 5> class U>
class Stack{
  private:
    int top, size;
    U <T> S;
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