#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"
#include "plot_functions.cpp"

using namespace std;
using namespace arma;







int main(int argc, char const *argv[]) {

  float deltaT = 1E-4;
  int T = 100; //number of years
  int N = T*1./deltaT;
  //string filename = "./data/test.txt";

  //float Gconst = 6.67408 * 1E-11;
  float Gconst = 4*M_PI*M_PI;
  float beta = 2;

  string method = "Velocity-Verlet";


  //number of timesteps saved to file pr. year
  int saved_timesteps = 50;

  bool relativistic_correction = true;
  //string filename = "./data/test.txt";
  //all_panets_plot(Gconst,beta,deltaT, N, filename, method, saved_timesteps, relativistic_correction);
  //string filename = "./data/runtimes.txt";
  //check_runtime(Gconst,beta,T, filename,relativistic_correction);
  string filename = "./data/stability.txt";
  check_stability(Gconst,beta,T, filename,relativistic_correction);


}
