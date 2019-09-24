#include <iostream>
#include <cmath>


class Neuron {
    public:
        double u;           // voltage across the neuron
        double threshhold;  // firing threshhold
        double r;           // resistance of the membrane
        double c;           // capacity of the activation
        double u_rest;      // resting voltage
        double u_reset;     // reset voltage
        double tau;         // charactaristic time

        void init(double threshhold,double r,double c,double u_rest,double u_reset,double u);
        double current(double u,double t);
        void du(double dt,double in_current);
};

void Neuron::init(double u_in,double threshhold_in,double r_in,double c_in,double u_rest_in,double u_reset_in){
    u = u_in;
    threshhold = threshhold_in;
    r = r_in;
    c = c_in;
    u_rest = u_rest_in;
    u_reset = u_reset_in;

    tau = r*c;
}

double Neuron::current(double u, double dt){
    if (u>threshhold){
        return (u_reset-u);
    } else {
        return 0;
    }
}

void Neuron::du(double dt,double in_current){
    u += dt*(1./tau)*(u_rest-u);    // leak current
    u += current(u,dt)+dt*r*in_current;         // activation current
}

double external_current(double t) {
    if (t>1. & t<10) {
        return 1.;
    } else {
        return 0;
    }
}