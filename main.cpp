#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"
#include "plot_functions.cpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {

  float deltaT = 1E-3; //timestep
  int T = 1; //number of years
  int N = T*1./deltaT; //number of integration points


  //gravitational constant
  float Gconst = 4*M_PI*M_PI;
  float beta = 2;

  //integration method
  string method = "Velocity-Verlet";


  //number of timesteps saved to file pr. year
  int saved_timesteps = 50;

  //true for relativistic_correction, false for not
  bool relativistic_correction = true;

  /*
  //This code will run all planets
  string filename = "./data/test.txt";
  all_panets_plot(Gconst,beta,deltaT, N, filename, method, saved_timesteps, relativistic_correction);
  */
  /*
  //This code will find the runtimes for the diffrent methods/deltaTs
  string filename = "./data/runtimes.txt";
  check_runtime(Gconst,beta,T, filename,relativistic_correction);
  */
  /*
  //This will check the energy_conserved
  string filename = "./data/stability.txt";
  check_stability(Gconst,beta,T, filename,relativistic_correction);
  */

}
