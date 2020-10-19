#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"

using namespace std;
using namespace arma;



void all_panets_plot(){
  int n = 4;
  planet *planets[n];
    planets[0] = new planet();
    planets[1] = new planet(3*1E-6,1,0,0,0,2*M_PI,0,"Earth");

}

int main(int argc, char const *argv[]) {
  int n = 2; //number of planets
  planet *planets[n];
    planets[0] = new planet();
    planets[1] = new planet(3*1E-6,1,0,0,0,2*M_PI,0,"Earth");
    //planets[2] = new planet(3*1E-6,2,0,0,0,2*M_PI*1./sqrt(2),0);
    //planets[3] = new planet(3*1E-6,3,0,0,0,2*M_PI*1./sqrt(3),0);

  //int len = end(planets)-begin(planets);

  float deltaT = 0.01;
  int N = 10000;
  string filename_data = "./data/test.txt";

  float Gconst = 4*M_PI*M_PI;
  float beta = 2;
  diff_solver *test;
  test = new diff_solver(Gconst,beta,n,planets);
  string method = "Velocity-Verlet";
  string plot_type = "Orbits";

  //lag noe saant saved timesteps pr year for aa
  //minske storrelse paa python array
  int saved_timesteps = 20;

  test->solve(deltaT,N,filename_data,method,plot_type);

  //delete test;
  //delete[] *planets;

}
