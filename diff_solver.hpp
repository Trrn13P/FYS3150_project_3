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
  float Gconst;


  planet **planets;



public:

  mat diffEq(mat current_XV, planet *planets[], int n);
  mat step(planet *planets[], int n,float deltaT);
  void solve(planet *planets[], int n,float deltaT, int N,string filename);


  diff_solver(float Gconst_,int n_,planet *planets_[n_]){
    Gconst = Gconst_;
    n = n_;
    //planet *planets[n] = planets_;
    planets = planets_;
    step(planets,n,0.001);
    //planet *planets[n];
    //planets = planets_;
  }
};


#endif
