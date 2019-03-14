#ifndef PROB_H

#define PROB_H
#include <vector>
#include <iostream>
using namespace std;

struct coord {double x, y, z;};

class Problem {
private:
	string name;
	string type;
	string comment;
	int dimension;
	string edge_weight_type;
	string edge_weight_form;
	string edge_data_form;
	string node_coord_type;
	vector<coord> node_coords;

	int distEuc2D(coord a, coord b);
	int distEuc3D(coord a, coord b);

public:
	void getInput(istream &in);
	int getDimension();
	string getName();
	string getType();
	string getComment();
	void printSpec();
	int distance(int i, int j);
};
# endif
