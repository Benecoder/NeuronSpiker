#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "neuron.h"

using namespace std;


double generator(double min, double max){
	double r_number = (double)rand()/RAND_MAX;
	double range = max-min;
	return min+range*r_number;
};

vector<double> vector_generator(double min,double max,int length) {
	vector<double> result(length);
	int i;
	for(i=0;i<length;i++){
		result[i] = generator(min,max);
	}
	return result;
}


class Connectome {
	public:
		int n_neurons;
		double pruning_threshhold;
		vector<vector<double> > weights;
		vector<Neuron> neurons;

		void random_init(int n_neurons_in,double pruning_threshhold);
		void prune_weights();
		void step(double dt);
};

void Connectome::prune_weights(){
	int i,j;
	for(i=0;i<n_neurons;i++){
		for(j=0;j<n_neurons;j++){
			if(weights[i][j] < pruning_threshhold){
				weights[i][j] = 0.;
			}
		}
	}
}

void Connectome::random_init(int n_neurons_in,double pruning_threshhold_in) {

	srand(3);
	
	n_neurons = n_neurons_in;
	pruning_threshhold = pruning_threshhold_in;

	int i;
	for(i=0;i<n_neurons;i++){

		//Connections		
		weights.push_back(vector_generator(-0.1,1.,n_neurons));

		//Nodes
		Neuron buffer_neuron;
		buffer_neuron.init(
			generator(-10.,10), 	// voltage
			generator(5.,25),		// firing threshhold
			generator(0.,1),		// resistance
			generator(0.,.5),		// capacity
			generator(-5.,5.),		// rest voltage
			generator(-30.,-10.),	// reset voltage
			generator(30.,30.));	// peak voltage
		neurons.push_back(buffer_neuron);

	}
	prune_weights();
}

void Connectome::step(double dt) {

	int neuron_index;
	int sec_neuron_index;
	double signal;

	vector<double> external_current(n_neurons);

	//collect external signals
	for(neuron_index=0;neuron_index<n_neurons;neuron_index++){
		for(sec_neuron_index=0;sec_neuron_index<n_neurons;sec_neuron_index++){
			signal = neurons[sec_neuron_index].u*weights[neuron_index][sec_neuron_index];
			external_current[neuron_index] += signal;
		}
	}

	//calculate step
	for(neuron_index=0;neuron_index<n_neurons;neuron_index++){
		neurons[neuron_index].du(dt,external_current[neuron_index]);
	}
}

int main(){


	Connectome Alpha;
	Alpha.random_init(300,0.3);

	double dt=0.01;
	double t;
	int i;

	cout << "t u1 u2 u3 u4 u5" << endl;

	for(t=0;t<10;t+=dt){
		Alpha.step(dt);
		cout << t << " ";
		for(i=0;i<300;i++){
			cout << Alpha.neurons[i].u << " ";
		}
		cout << endl;
	}

	return 0;
}