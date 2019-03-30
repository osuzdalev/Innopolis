#include <iostream>
#include <vector>
#include "searcher.h"

using namespace std;

bool func(int x){
	return (x < 100);
}

int main(){
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	cout << *(searcher::find5(arr.begin(), arr.end(), func));
}