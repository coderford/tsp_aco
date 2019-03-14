#include "problem.h"
#include "utils.h"
#include <iostream>
#include <cmath>
using namespace std;

int Problem::getDimension() { return dimension; }
string Problem::getName() { return name; }
string Problem::getType() { return type; }
string Problem::getComment() { return comment; }

int Problem::distEuc2D(coord a, coord b) {
	return nint(sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
}

int Problem::distEuc3D(coord a, coord b) {
	return nint(sqrt((a.x - b.x)*(a.x - b.x) + 
					 (a.y - b.y)*(a.y - b.y) +
					 (a.z - b.z)*(a.z - b.z)));
}

int Problem::distance(int i, int j) {
	// nodes will be 0 indexed...
	if(edge_weight_type == "EUC_2D") 
		return distEuc2D(node_coords[i], node_coords[j]);
	else if(edge_weight_type == "EUC_3D") 
		return distEuc3D(node_coords[i], node_coords[j]);
}

void Problem::getInput(istream &in) {
	string line;
	string varname;
	string val;
	int colon;

	while(!in.eof()) {
		getline(in, line);
		colon = line.find(':');
		if(colon != string::npos) {
			if(line[colon-1] == ' ')
				varname = line.substr(0, colon - 1);
			else varname = line.substr(0, colon);
			if(line[colon+1] == ' ')
				val = line.substr(colon + 2, line.length() - (colon + 2));
			else val = line.substr(colon + 1, line.length() - (colon + 1));
		}
		else varname = line;
		if(varname == "NAME") name = val;
		if(varname == "COMMENT") comment = val;
		if(varname == "TYPE") type = val;
		if(varname == "DIMENSION") dimension = atoi(val.c_str());
		if(varname == "EDGE_WEIGHT_TYPE") edge_weight_type = val;
		if(varname == "NODE_COORD_TYPE") node_coord_type = val;
		if(varname == "NODE_COORD_SECTION") {
			bool is3d = true;
			if(edge_weight_type == "EUC_2D") is3d = false;
			for(int i = 0; i<dimension; i++) {
				int idx;
				coord c;

				in>>idx>>c.x>>c.y;
				if(is3d) cin>>c.z;
				else c.z = 0;

				node_coords.push_back(c);
			}
			in.get();
		}
		if(varname == "EOF") break;
	}
}

void Problem::printSpec() {
	cout<<"========================================================"<<endl;
	cout<<" PROBLEM: "<<getName()<<endl;
	cout<<" TYPE: "<<getType()<<endl;
	cout<<" COMMENT: "<<getComment()<<endl;
	cout<<" DIMENSION: "<<getDimension()<<endl;
	cout<<"========================================================"<<endl;
}

