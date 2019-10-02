#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double random_generator(double min, double max){
  double r_number = (double)rand()/RAND_MAX;
  double range = max-min;
  return min+range*r_number;
};


typedef  vector<vector<double> > Matrix;

vector<double> random_vector_generator(double min,double max,int length) {
	vector<double> result(length);
	int i;
	for(i=0;i<length;i++){
		result[i] = random_generator(min,max);
	}
	return result;
}


Matrix get_xor_data(int length) {
	vector<double> row(3);
	Matrix result(length,row);
	int i,j;

	//in data
	for(i=0;i<length;i++){
		for(j=0;j<2;j++){
			row[j] = (double) (rand()%2);
		}
		result[i] = row;
	}


	//out data
	bool in_1,in_2;
	for(j=0;j<length;j++){
		in_1 = (bool)result[j][0];
		in_2 = (bool)result[j][1];
		result[j][2] = (double)(in_1^in_2);
	}

	return result;
}