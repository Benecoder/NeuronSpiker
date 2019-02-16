#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double u_rest = -10;
double u_r = -15;
double r = 35;
double tau = 0.6;
double dt = 1.e-3;
double threshhold = 15;

double i(double t){

    if (t>1.&&t<10.0){
        return 1.;
    } else {
        return 0.;
    }
}

double du(double u,double t){
    double du_dt = (1/tau)*(u_rest-u+r*i(t));
    if (u>=threshhold) {
        return du_dt*dt+(u_r-u);
    } else {
        return du_dt*dt;
    }
}

int main(){
    
    double t;
    double u = u_rest;

    
    for(t=0;t<20;t+=dt){
        u += du(u,t);
        cout << t << " " << u << " " << i(t) << endl;
    }
    
    return 0;
}