#ifndef ANTSYS_H
#define ANTSYS_H

#include "problem.h"
#include <vector>
using namespace std;

class AntSystem {
private:
	int m, alpha, beta; 
	double rho, Q;
	Problem *prob;
	vector<vector<double> > tau;
	vector<int> best_path;
	int best_cost;

	void oneIteration();
	void initPheromones();
	double moveProbability(int i, int j, int k, vector<vector<bool> > &used);
	
public:
	AntSystem(Problem *p, int m, double rho, int alpha, int beta, double Q);
	AntSystem(Problem *p, int m);
	void run(int num_iters);
	void printSolution();
};

#endif
