// Test Array template that accepts template as a parameter

#include <iostream>

#include "Stack.hpp"
#include "Array.hpp"
#include "List.hpp"

using namespace std;

typedef struct{
  int a;
}myType;



int main(){

  // See the requirements in the files of the previous week excersize

  int score = 0;
  int max_score = 1;

  // Test Stack with Array
  try{
      Stack<int,Array> *a = new Stack<int,Array>();
      a->empty();
      score++;
      cout << "01 success" << endl;
  }catch(...){
    cout << "01 failure" << endl;
  }

  // Test Stack with List
  try{
      Stack<int,List> *b = new Stack<int,List>();
      b->empty();
      // score++;
      cout << "02 success" << endl;
  }catch(...){
    cout << "02 failure" << endl;
  }

  cout << "score: " << score << "/" << max_score << endl;
  // Stack<int,Array> *a = new Stack<int,Array>();
  // Stack<int,List> *b = new Stack<int,List>();


  return 0;
}
