#include <iostream>
#include <cmath>

using namespace std;

double u_r = -30.;
double threshhold = 20.;
double r = 32;
double u_rest = -10.;
double tau = 0.4;
double dt = 1e-4;
double length = 20.;

double u1_buffer;
double u2_buffer;

double current(double t){
    if (t>1. & t< 10.){
        return 1;
    } else {
        return 0.;
    }
}

double spike_current(double u){
    if (u>threshhold){
        return (u_r-u)/dt;
    } else {
        return 0.;
    }
}

double du_dt(double t,double u){
    return (-1/tau)*( (u-u_rest)-r*(current(t)+spike_current(u)) );
}



int main(){
    
    double u = u_rest;
    double t;
    
    for(t=0;t<length;t+=dt){
        u += dt*du_dt(t,u);
        cout << t << " " << u << " " << current(t) <<  endl;
    }

    return 0;
}