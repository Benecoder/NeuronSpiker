#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>
#include "neuron3.h"


using namespace std;


class Connectome {
	public:
		int n_neurons;
		double pruning_threshhold;
		Matrix weights;
		vector<Neuron> neurons;

		void random_init(int seed,int n_neurons_in,double pruning_threshhold);
		void parameter_propagator(int seed);
		void prune_weights();
		void step(double dt,vector<double> input);
		void simulate(double dt,Matrix stimulation_data);
		void frequency_analysis(string output_name,double dt);
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


void Connectome::random_init(int seed,int n_neurons_in,double pruning_threshhold_in) {

	srand(seed);
	
	n_neurons = n_neurons_in;
	pruning_threshhold = pruning_threshhold_in;

	int i;
	for(i=0;i<n_neurons;i++){

		//Connections		
		weights.push_back(random_vector_generator(-1.,.1,n_neurons));

		//Nodes
		Neuron buffer_neuron;
		buffer_neuron.init(
			5., 	// voltage across the neuron
			13.,		// firing threshhold
			30.,		// reset threshhold
			random_generator(0.2,4.),	// resistance of the membrane
			random_generator(0.,.1),	// capacity of the activation
			2.,			// sharpness of the peak
			-3.,	// resting voltage
			-10.,	// reset voltage
            .2);			// refactorisation time

		neurons.push_back(buffer_neuron);

	}
	prune_weights();
}

void Connectome::parameter_propagator(int seed){

	srand(seed);
	int i,j;
	double spread = 0.1;

	for(i=0;i<n_neurons;i++){
		neurons[i].r += random_generator(-spread,spread);
		neurons[i].c += random_generator(-spread,spread);
		for(j=0;j<n_neurons;j++){
			weights[i][j] += random_generator(-spread,spread);
		} 
	}
}


void Connectome::step(double dt,vector<double> input) {

	int neuron_index;
	int sec_neuron_index;
	double signal;

	vector<double> external_current(n_neurons);

	int stimulated_neurons=input.size();

	//collect external signals
	for(neuron_index=0;neuron_index<n_neurons;neuron_index++){
		for(sec_neuron_index=0;sec_neuron_index<n_neurons;sec_neuron_index++){
			signal = neurons[sec_neuron_index].u*weights[neuron_index][sec_neuron_index];
			external_current[neuron_index] += signal;
		}
		if(neuron_index<stimulated_neurons){
			external_current[neuron_index] += input[neuron_index];
		}
	}


	//calculate step
	for(neuron_index=0;neuron_index<n_neurons;neuron_index++){
		neurons[neuron_index].step(dt,external_current[neuron_index]);
	}
}

void Connectome::simulate(double dt,Matrix in_data){

	double t;
	int i,j;
	double time_length=in_data.size()*dt;

	ofstream activation_data;
	activation_data.open("network.2.csv");

	for(i=0;i<in_data.size();i++){
		t = i*dt;
		activation_data << t << " ";
		for(j=0;j<n_neurons;j++){
			activation_data << neurons[j].u << " ";
		}
		activation_data << endl;
		step(dt,in_data[i]);
	}

	activation_data.close();
}

void Connectome::frequency_analysis(string output_name, double dt){

	double t;
	int i,j;
	double n_steps = 1000;
	double time_length=n_steps*dt;
	vector<double> in_data(n_neurons,0.);
	vector<double> last_firing(n_neurons,0.);
	vector<double> frequency(n_neurons,0.);

	ofstream frequency_data;
	frequency_data.open(output_name);

	for(i=0;i<n_steps;i++){
		t = i*dt;
		frequency_data << t << " ";
		for(j=0;j<n_neurons;j++){

			// calculates freuqency if new spike is recorded
			if (neurons[j].u == neurons[j].r_threshhold) {
				frequency[j] = 1./(t-last_firing[j]);
				last_firing[j] = t;
			}

			frequency_data << frequency[j] << " ";
		}
		frequency_data << endl;

		step(dt,in_data);
	}

	frequency_data.close();
}


