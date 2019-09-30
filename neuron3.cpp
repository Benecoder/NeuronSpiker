#include <iostream>
#include <cmath>

/* exponential firing model with resting period*/


using namespace std;

double generator(double min, double max){
  double r_number = (double)rand()/RAND_MAX;
  double range = max-min;
  return min+range*r_number;
};



class Neuron {
    public:
        double u;           // voltage across the neuron
        double f_threshhold;// firing threshhold
        double r_threshhold;// reset threshhold
        double r;           // resistance of the membrane
        double c;           // capacity of the activation
        double delta_t;     // shrapness of the peak
        double u_rest;      // relaxed voltage
        double u_reset;     // reset voltage
	double refrac_t;    // refractory period
        double tau;         // charactaristic time
	double refrac_timer;// timer since the last firing

        void init(double u,
                  double f_threshhold,
                  double r_threshhold,
                  double r,
                  double c,
                  double delta_t,
                  double u_rest,
                  double u_reset,
		  double refrac_t);
        double du(double dt,double in_current);
        void step(double dt,double in_current);
};

void Neuron::init(double u_in,
                  double f_threshhold_in,
                  double r_threshhold_in,
                  double r_in,
                  double c_in,
                  double delta_t_in,
                  double u_rest_in,
                  double u_reset_in,
		  double refrac_t_in){

    u = u_in;
    f_threshhold = f_threshhold_in;
    r_threshhold = r_threshhold_in;
    r = r_in;
    c = c_in;
    delta_t = delta_t_in;
    u_rest = u_rest_in;
    u_reset = u_reset_in;
    refrac_t = refrac_t_in;

    tau = r*c;
    refrac_timer = refrac_t;
}

double Neuron::du(double dt,double in_current) {
  if (u < r_threshhold & (refrac_timer >= refrac_t)) {
    double result;
    result = u_rest-u;
    result += delta_t*exp((u-f_threshhold)/delta_t)+r*in_current;
    return fmin(result*dt,r_threshhold-u);

  } else if (u< r_threshhold){
    double result;
    f_threshhold = (refrac_t/refrac_timer)*f_threshhold;
    result = u_rest-u;
    result += delta_t*exp((u-f_threshhold)/delta_t)+r*in_current;
    refrac_timer += dt;
    return fmin(result*dt,r_threshhold-u);

  } else {
    refrac_timer = 1.e-3;
    return u_reset-u;
  }
}

void Neuron::step(double dt,double in_current){
    u += du(dt,in_current);
}

int main(){

  Neuron Alpha;
  Alpha.init(-0.5,15.,40.,2.,.2,.1,2.,-4.,3.);

  double t;

  cout << "t u f_threshhold r_threshhold refrac_timer/refrac_t" << endl;

  for(t = 0;t<40;t+=0.005){
    cout << t << " " << Alpha.u << " ";
    cout << Alpha.f_threshhold << " ";
    cout << Alpha.r_threshhold << " ";
    cout << Alpha.refrac_t/Alpha.refrac_timer << endl;
    Alpha.step(0.01,3.5);
  }

  return 0;
}

