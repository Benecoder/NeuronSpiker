#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "neuron3.h"

using namespace std;


class Connectome {
	public:
		int n_neurons;
		double pruning_threshhold;
		Matrix weights;
		vector<Neuron> neurons;

		void random_init(int n_neurons_in,double pruning_threshhold);
		void prune_weights();
		void step(double dt,vector<double> input);
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
		weights.push_back(random_vector_generator(-1.,.1,n_neurons));

		//Nodes
		Neuron buffer_neuron;
		buffer_neuron.init(
			random_generator(0.,10), 	// voltage across the neuron
			random_generator(0.,18),	// firing threshhold
			30,			// reset threshhold
			random_generator(0.2,4.),	// resistance of the membrane
			random_generator(.1,.1),	// capacity of the activation
			2.,			// sharpness of the peak
			random_generator(-3.,5.),	// resting voltage
			random_generator(-10.,-5.),	// reset voltage
            .2);			// refactorisation time

		neurons.push_back(buffer_neuron);

	}
	prune_weights();
}


void Connectome::step(double dt,vector<double> input) {

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
		external_current[neuron_index] += input[neuron_index]; 
	}


	//calculate step
	for(neuron_index=0;neuron_index<n_neurons;neuron_index++){
		neurons[neuron_index].step(dt,external_current[neuron_index]);
	}
}

//void Connectome::simulate_input(Matrix in_data){

//}

int main(){

	Connectome Alpha;
	Alpha.random_init(400,-0.1);

	double dt=0.05;
	double t;
	int i;

	vector<double> stimulation((int)50.0/dt);

	for(i=0;i<100;i++){
		stimulation[i] = 5.;
	}

	cout << "t u1 u2 u3 u1_ft u2_ft u3_ft" << endl;

	for(t=0;t<50;t+=dt){
		cout << t << " ";
		Alpha.step(dt,stimulation);
		for(i=0;i<400;i++){
			cout << (double) (Alpha.neurons[i].u >= Alpha.neurons[i].r_threshhold) << " ";
		}
		cout << endl;
	}

	return 0;
}
