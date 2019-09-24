#include <iostream>
#include <cmath>

using namespace std;

double threshhold = 22.;
double r = 20;
double u_rest = 10.;
double u_reset = -20;
double tau = 0.4;
double dt = 1e-4;
double length = 20.;

double u1_buffer;
double u2_buffer;

double current(double t,double u){
    if (u>threshhold){
        return (tau*(u_reset-u))/(dt*r);
    } else if (t>1. & t< 10.){
        return 1;
    } else {
        return 0.;
    }
}

double leak_potential_change(double u) {
    return (1./tau)*(u_rest-u);
}

double activation_potential_change(double t,double u){
    return (1./tau)*r*(current(t,u));
}


int main(){
    
    double u = u_rest;
    double t;

    cout << "time u(t) u_reset u_rest current" << endl;
    
    for(t=0;t<length;t+=dt){
        u += dt*(leak_potential_change(u)+activation_potential_change(t,u));
        cout << t << " ";
        cout << u << " ";
        cout << u_reset << " ";
        cout << u_rest << " ";
        cout <<  endl;
    }

    return 0;
}