#include <iostream>

using namespace std;

int max(int a, int b) { return (a > b)? a : b; }

int knapSack(int W, int wt[], int val[], int n){
	if(wt[n-1] > W) return knapSack(W, wt, val, n-1);
	
	else return max(val[n-1] + knapSack(W-wt[n-1], wt, val, n-1), knapSack(W, wt, val, n-1));
}

int main() {
	int val[5] = {10, 120, 100, 10, 60};
	int wt[5] = {5, 30, 5, 20, 10};
	int W = 50;
	int n = sizeof(val)/sizeof(val[0]);
	printf("%d", knapSack(W, wt, val, n));
	return 0;
}