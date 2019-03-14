#include "antsystem.h"
#include "utils.h"
#include <cmath>

AntSystem::AntSystem(Problem *p, int m, double rho, int alpha, 
int beta, double Q)
{
	this->prob = p;
	this->m = m;
	this->rho = rho;
	this->alpha = alpha;
	this->beta = beta;
	this->Q = Q;
	this->best_cost = INF;

	initPheromones();
}

AntSystem::AntSystem(Problem *p, int m) {
	this->prob = p;
	this->m = m;
	this->rho = 0.2;
	this->alpha = 1;
	this->beta = 1;
	this->Q = 1;
	this->best_cost = INF;

	initPheromones();
}

void AntSystem::initPheromones() {
	int n = prob->getDimension();
	tau.assign(n, vector<double>(n, 0));
}

void AntSystem::oneIteration() {
	// give random start point to each ant...
	int n = prob->getDimension();
	vector<vector<int> > paths(m, vector<int>());	
	vector<vector<bool> > used(m, vector<bool>(n, false));
	vector<int> tour_lengths(m, 0);

	for(int k = 0; k<m; k++) {
		paths[k].push_back(randint(0, n-1));
		used[k][paths[k][0]] = true;
	}
	int len = 0;
	while(len < n-1) {
		// choose next node for each ant
		for(int k = 0; k<m; k++) {
			// calculate probability for each remaining node and then
			// use roulette selection
			vector<int> remaining;		// the remaining nodes
			vector<double> P;			// probabilities

			for(int i = 0; i < n; i++) {
				if(!used[k][i]) {
					remaining.push_back(i);
					P.push_back(moveProbability(paths[k][len], i, k, used));
				}
			}
			
			int selected = rouletteSelect(P.size(), P);
			paths[k].push_back(remaining[selected]);
			used[k][remaining[selected]] = true;
			tour_lengths[k] += prob->distance(paths[k][len], paths[k][len+1]);
		}
		len++;
	}

	// add first node to paths again:
	for(int k = 0; k<m; k++) {
		paths[k].push_back(paths[k][0]);
		tour_lengths[k] += prob->distance(paths[k][len], paths[k][len+1]);
	}

	// store best path:
	int min_cost = tour_lengths[0];
	int min_index = 0;
	for(int k = 1; k<m; k++) {
		if(tour_lengths[k] < min_cost) {
			min_cost = tour_lengths[k];
			min_index = k;
		}
	}
	if(min_cost < best_cost) {
		best_cost = min_cost;
		best_path = paths[min_index];
	}

	// update pheromone decay
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			tau[i][j] *= (1-rho);
		}
	}

	// use path vectors to add to pheromone levels
	for(int k = 0; k<m; k++) {
		for(int i = 1; i<=n; i++) {
			tau[paths[k][i-1]][paths[k][i]] += (double)Q/(tour_lengths[k]);
			tau[paths[k][i]][paths[k][i-1]] = tau[paths[k][i-1]][paths[k][i]];
		}
	}
}

double AntSystem::moveProbability(int i, int j, int k, 
vector<vector<bool> > &used) 
{
	int n = prob->getDimension();
	double numerator = pow(tau[i][j], alpha);
	numerator *= pow(1.0/(double)prob->distance(i, j), beta);

	double denominator = 0;
	for(int l = 0; l<n; l++) {
		if(!used[k][l]) {
			double tmp = pow(tau[i][l], alpha);
			tmp *= pow(1.0/(double)prob->distance(i, l), beta);
			denominator += tmp;
		}
	}
	if(numerator == 0 && denominator == 0) denominator = 1;
	return numerator/denominator;
}

void AntSystem::run(int iters) {
	while(iters--) {
		cout<<" Iteration "<<iters<<", ";
		oneIteration();
                cout<<"Best cost so far: "<<best_cost<<'\n';
	}
}

void AntSystem::printSolution() {
	// print path and cost:
        cout<<"\n Best path:\n ";
        for(int i = 0; i<best_path.size(); i++) {
            cout<<best_path[i];
            if(i < best_path.size()-1) cout<<'>';
        }
        cout<<'\n';
	cout<<" Cost: "<<best_cost<<'\n';
}
