#include "antsystem.h"
#include "problem.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	Problem p1;
	ifstream input;
	if(argc > 1) {
		input.open(argv[1], ios_base::in);
		if(input.fail()) {
			cout<<"FILE NOT FOUND!\n";
			return 1;
		}
	}
	else {
		cout<<"Usage: aco FILENAME\n";
		return 0;
	}
	p1.getInput(input);
	p1.printSpec();
	input.close();
	
	int m, iters;
	cout<<" Number of ants: ";
	cin>>m;
	cout<<" Number of Iterations: ";
	cin>>iters;
	AntSystem a1(&p1, m);
	a1.run(iters);
	a1.printSolution();
	return 0;
}
