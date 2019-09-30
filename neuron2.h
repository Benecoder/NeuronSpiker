#include <iostream>
#include <cmath>

/* exponential firing model */


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
        double tau;         // charactaristic time

        void init(double u,
                  double f_threshhold,
                  double r_threshhold,
                  double r,
                  double c,
                  double delta_t,
                  double u_rest,
                  double u_reset);
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
                  double u_reset_in){

    u = u_in;
    f_threshhold = f_threshhold_in;
    r_threshhold = r_threshhold_in;
    r = r_in;
    c = c_in;
    delta_t = delta_t_in;
    u_rest = u_rest_in;
    u_reset = u_reset_in;

    tau = r*c;
}

double Neuron::du(double dt,double in_current) {
  if (u < r_threshhold) {
    double result;
    result = u_rest-u;
    result += delta_t*exp((u-f_threshhold)/delta_t)+r*in_current;
    result += delta_t*exp((u_reset-u)/delta_t);
    result += generator(-2,2);
    return fmin(result,r_threshhold-u);
  } else {
    return u_reset-u;
  }
}

void Neuron::step(double dt,double in_current){
    u += du(dt,in_current);
}

/*int main(){

  Neuron Alpha;
  Alpha.init(-0.5,15.,40.,5.,0.4,1.,1.,-3.);


  double t;

  cout << "t u f_threshhold r_threshhold" << endl;

  for(t = 0;t<40;t+=0.005){
    Alpha.step(0.01,);
    cout << t << " " << Alpha.u << " ";
    cout << Alpha.f_threshhold << " ";
    cout << Alpha.r_threshhold << endl;
  }

  return 0;
}*/

