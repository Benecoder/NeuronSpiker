#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "network.h"


using namespace std;
int n_neurons = 400;
double dt= 0.05;

vector<double> get_target(int n_neurons){

	vector<double> result(n_neurons,0);
	int i;
	for(i=0;i<n_neurons;i++){
		result[i] = (float)(i%2)*2.+1.;
	}
	return result;
}


double connectome_cost(vector<int> genetic_code,vector<double>target){

	Connectome subject;
	subject.random_init(genetic_code[0],n_neurons);

	int i;
	for(i=1;i<genetic_code.size();i++){
		subject.parameter_propagator(genetic_code[i]);
	}

	vector<double> calculation = subject.frequency_analysis(500.);
    
    double cost = 0.;
    for(i=0;i<n_neurons;i++){
    	cost += pow(calculation[i]-target[i],2.);
    }

    return (float) cost/n_neurons;
}

vector<double> pop_cost(vector<vector<int> > genetic_codes,vector<double> target){


	vector<double> result(genetic_codes.size(),0);
	int i;


	for(i=0;i<genetic_codes.size();i++){
		result[i] = connectome_cost(genetic_codes[i],target);
	}

	cout << "Finished loading results" << endl;
	return result;
}

int main(){

	int n_neurons = 400;
	vector<double> target = get_target(n_neurons);

	vector<vector<int> > genetic_codes;
	int pop_size = 10;

	int i;
	for (i=0;i<pop_size;i++){
		vector<int> member(1.,i);
		genetic_codes.push_back(member);
	}

	for(i=0;i<10;i++){
		genetic_codes[0].push_back(i*2);
	}

	vector <double> pop_cost_eval(pop_size,0);
	pop_cost_eval = pop_cost(genetic_codes,target);

    
	return 0;
}