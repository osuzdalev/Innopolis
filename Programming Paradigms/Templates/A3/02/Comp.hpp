/*
Write a template for a class Comp that has one static method bool lesser(v1,v2).
 This method accepts two values of the same type and returns true when v1<v2,
 and false otherwise. Use lecture slides as reference.

1. The name of the class should be precisely Comp
2. The method lesser should be static
3. The method lesser returns bool value

4. Write a class specialization that accepts the type const char*. The function
    for comparing two strings should be strcmp(v1,v2)<0

5. Write a class specialization that accepts pointers. The comparison is done
    by dereferencing the pointers first.

6. Write class specialization that accepts pointers to functions as arguments
    of the function lesser(). Functions that are provided as arguments accept
    no parameters.

Testing of your implementation will be done by calling expressions similar
to the following:
  Comp<int>::lesser(a1,b1)
  Comp<double>::lesser(a2,b2)
  Comp<int*>::lesser(a3,b3)
  Comp<const char*>::lesser(a4,b4)
  Comp<int(*)()>::lesser(a5,b5)

Do not use any libraries other than listed below.

Failure to comply with any requirements will result in failure during
compilation and the 0 points for the current problem.
*/

#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class Comp{
  public:
    static bool lesser(const T& v1, const T& v2){
      return v1<v2;
    }
};

template<>
class Comp<const char*>{
  public:
    static bool lesser(const char* v1, const char* v2){
      return strcmp(v1, v2)<0;
    }
};

template<typename T>
class Comp<T*>{
  public:
    static bool lesser(T* v1, T* v2){
      return *v1<*v2;
    }
};

template<typename T>
class Comp<T(*)()>{
  public:
    static bool lesser(T(*v1)() , T(*v2)() ){
      return (*v1)()<(*v2)();
    }
};