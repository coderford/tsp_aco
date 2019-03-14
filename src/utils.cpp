#include "utils.h"
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

int nint(double x) { return (int) (x + 0.5); }

int randint(int low, int high) {
	return rand()%(high-low) + low;
}

int rouletteSelect(int n, vector<double> &P) {
	if(n == 1) return 0;
	for(int i = 1; i<n; i++) 
		P[i] += P[i-1];
	
	if(P[n-1] < 0.000001) return randint(0, n-1);
	double r = (double)rand()/RAND_MAX;
	for(int i = 0; i<n; i++) {
		if(P[i] >= r) return i;
	}
	cout<<"Roulette-select failed!\n";
	return 0;
}

