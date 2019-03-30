#include <iostream>
#include <list>
#include <vector>

#include "Head.h"

#define N 3

using namespace std;

template <typename T>
bool x(T a ){
	return  a < 9;
}

template<>
bool x(bool a){
	return a;
}

template <>
bool x(char a){
	return a < 'z';
}

//arrays
int integers[N] = {0, 1, 2};
bool bools[N] = {0, 1, 0};
char chars[N] = {'a', 'b', 'c'};
float floats[N] = {0.0, 1.0, 2.0};

//vectors
vector<int> vect;
//list
list<int> lst;

int main() {
	searcher S1, S2, S3, S4, S5, S6;
	int* result_1;
	bool* result_2;
	char* result_3;
	float* result_4;
	//result_1 = S1.find5(integers,&integers[N],x);
	//cout << * result_1 << endl;
	result_2 = S2.find5<bool, bool*>(&bools[0],&bools[N],x);
	cout << * result_2 << endl;
	result_3 = S3.find5<char, char*>(&chars[0],&chars[N],x);
	cout << * result_3 << endl;
	result_4 = S4.find5<float, float*>(&floats[0],&floats[N],x);
	cout << * result_4 << endl;
	
	vector<int>::iterator result_5;
	vect.push_back(0);
	vect.push_back(1);
	vect.push_back(2);
	result_5 = S5.find5<int, vector<int>::iterator >(vect.begin(), vect.end(),x);
	cout << *result_5;
	
	list<int>::iterator result_6;		
	lst.push_back(0);
	lst.push_back(1);
	lst.push_back(2);
	result_6 = S6.find5<int, list<int>::iterator>(lst.begin(),lst.begin(),x);
	cout << * result_6 << endl;
	return 0;
}