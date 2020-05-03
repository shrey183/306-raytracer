#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>
#include <cmath>
#include <random>


#include "vector.h"
#include "ray.h"

using namespace std;
static std:: default_random_engine engine(10);
static std:: uniform_real_distribution<double> uniform (0, 1); 

inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double random_double(){
  return uniform(engine);
}


void boxMuller(double stdev, double& x, double& y){
	double r1 = random_double();
  double r2 = random_double();
  x += sqrt(-2 * log(r1)) * cos(2 * M_PI * r2) * stdev;
  y += sqrt(-2 * log(r1)) * sin(2 * M_PI * r2) * stdev;
}


double schlick(double omega_N, double ref_idx) {
    double k0 = (1-ref_idx) / (1+ref_idx);
    k0 = k0*k0;
    return k0 + (1-k0)*pow((1 - abs(omega_N)),5);
}


double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

Vector random_cos(const Vector &N){
    double r1 = random_double();
    double r2 = random_double();
    double x = cos(2*M_PI*r1)*sqrt(1-r2);
    double y = sin(2*M_PI*r1)*sqrt(1-r2);
    double z = sqrt(r2);
    double small = min(min(abs(N[0]), abs(N[1])), abs(N[2]));
    Vector T1;
    for (int i = 0; i<3;i++){
        if(abs(N[i]) == small){
            if(i == 0){
                T1 = Vector(0,-N[2], N[1]);
            }
            else if(i == 1){
                T1 = Vector(- N[2], 0, N[0]);
            }
            else{
                T1 = Vector(- N[1], N[0], 0);
            }
        }
    }
    T1 = T1.normalize();
    Vector T2 = cross(N, T1);
    return x*T1 + y*T2 + z*N;

}


#endif
