#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {
  int n = 4; //number of planets
  planet *planets[n];
    planets[0] = new planet();
    planets[1] = new planet(3*1E-6,1,0,0,0,1.4*2*M_PI,0);
    planets[2] = new planet(3*1E-6,2,0,0,0,2*M_PI*1./sqrt(2),0);
    planets[3] = new planet(3*1E-6,3,0,0,0,2*M_PI*1./sqrt(3),0);

  //int len = end(planets)-begin(planets);

  float deltaT = 0.01;
  int N = 5000;
  string filename = "./data/test.txt";

  float Gconst = 4*M_PI*M_PI;
  float beta = 2;
  diff_solver *test;
  test = new diff_solver(Gconst,beta,n,planets);
  string method = "RK4";
  test->solve(deltaT,N,filename,method);

  delete test;
  delete[] *planets;

}
