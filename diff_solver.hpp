#include <armadillo>
#include <iostream>
#include "planet.h"

using namespace std;
using namespace arma;

#ifndef DIFF_SOLVER_HPP
#define DIFF_SOLVER_HPP
#include "planet.h"

class diff_solver {
private:
  //number of planets
  int n;
  //gravitational constant
  float Gconst;
  //true of false relativistic correction
  bool relativistic_correction;
  //timestep deltaT
  float deltaT;

  //integration method
  string method;
  //0 if error message, 1 if not, it shows if you input a invalid integration method
  int error_message;

  float beta;
  float speed_of_light; // AU/yr;

  //pointer to all planets
  planet **planets;



public:
  //runtime for time it takes to integrate, start is start of integration, finish is end of integration
  float runtime, start, finish;

  //all functions
  mat diffEq(mat current_XV);
  mat step(string method_);
  void solve(float deltaT_, int N, string filename,string method_,string plot_type, int step_saved,bool relativistic_correction_);
  float solve_test(float deltaT_, int N, string method_, bool relativistic_correction_);


  diff_solver(float Gconst_,float beta_,int n_,planet *planets_[n_]){
    speed_of_light = 63239.7263; // AU/yr;
    error_message = 1;
    Gconst = Gconst_;
    beta = beta_;
    n = n_;
    planets = planets_;

  }
};


#endif
