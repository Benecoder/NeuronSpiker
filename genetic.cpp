#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>
#include "network.h"


using namespace std;


int main(){

	vector<vector<int> > genetic_code;
	int pop_size = 30;

	int i;
	for (i=0;i<30;i++){
		vector<int> member(1.,i);
		genetic_code.push_back(member);
	}

	Connectome pop_zero;
	pop_zero.random_init(4,400,-0.1);
	pop_zero.parameter_propagator(8);

	pop_zero.frequency_analysis("genetic.csv",0.05);

	return 0;
}