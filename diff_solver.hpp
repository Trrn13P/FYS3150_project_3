#include <armadillo>
#include "planet.h"

using namespace arma;

#ifndef DIFF_SOLVER_HPP
#define DIFF_SOLVER_HPP
#include "planet.h"

class diff_solver {
private:
  int total_planets;
  //number of planets
  int n;


  planet* planets[];



public:
  void addPlanet(planet newplanet);
  mat diffEq(mat current_XV);
  void calcSlope(mat current_XV);
  void step();

  diff_solver(int n_){
    total_planets = 0;
    n = n_;
  }

};


#endif
