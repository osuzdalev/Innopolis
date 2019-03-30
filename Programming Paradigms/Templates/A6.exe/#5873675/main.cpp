#include <iostream>
using namespace std;

#ifndef UNTITLED_FIND_H
#define UNTITLED_FIND_H
/**
 *
 * @tparam Typename
 * @tparam Pointer to Typename
 * @param first
 * @param beyond
 * @param compare function
 * @return Pointer to result
 *
 *Type T should support operator!=().
 *Type P should support operator*();  this operator should return a value of type T.
 *Type P should support operator++(); the result should denote the next element of the data structure.
 *Type P should support operator--(); the result should denote the next element of the data structure.
 *Type P should support operator-(); the result should denote the next element of the data structure.
 *Type P should support operator!=().
 *
 *
 */
template < typename T, typename P >
P find ( P first, P beyond, bool (*c)(T))
{
    P p = beyond - 1;
    while ( p != first - 1 && !c(*p)) {
        p--;
    }
    return p;
}

#endif //UNTITLED_FIND_H

template <typename T>
bool x(T a ){
    return  a < 9;
}

int main() {
    int* result;

    cout << "array :";
    int a[] = {1,2,3,4,6,8,10,12,14,16,32,64,128,256};
    for(int i =0; i < 14; i++) cout << a[i] << "\t";
    result = find<int,int*>(&a[0],&a[14],x<int>);
    if (result != &a[-1])
        cout<< endl<< "les then 9 (last element) :"<< *result  << endl;
    else
        cout<< endl<< "les then 9 (last element) : impossible to find"  << endl;

    cout << "array :";
    int b[] = {9,9,9,9,9,9,10,12,14,16,32,64,128,256};
    for(int i =0; i < 14; i++) cout << b[i] << "\t";
    result = find<int,int*>(&b[0],&b[14],x<int>);
    if (result != &b[-1])
        cout<< endl<< "les then 9 (last element) :"<< *result  << endl;
    else
        cout<< endl<< "les then 9 (last element) : impossible to find"  << endl;

    return 0;
}