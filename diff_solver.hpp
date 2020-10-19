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

  float deltaT;

  string method;

  int error_message;

  float beta;

  planet **planets;



public:

  mat diffEq(mat current_XV);
  mat step(string method_);
  void solve(float deltaT_, int N, string filename,string method_,string plot_type, int step_saved);


  diff_solver(float Gconst_,float beta_,int n_,planet *planets_[n_]){
    error_message = 1;
    Gconst = Gconst_;
    beta = beta_;
    n = n_;
    planets = planets_;



  }
};


#endif
