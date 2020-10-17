#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"

using namespace std;
using namespace arma;

mat diffEq(mat current_XV, planet *planets[], int n);
mat step(planet *planets[], int n,float deltaT);
void solve(planet *planets[], int n,float deltaT, int N,string filename);

int main(int argc, char const *argv[]) {
  int n = 2; //number of planets
  planet *planets[n];
    planets[0] = new planet();
    planets[1] = new planet(3*1E-6,1,0,0,0,2*M_PI,0);
    //planets[2] = new planet(3*1E-6,2,0,0,4*M_PI,0,0);
    //planets[3] = new planet(3*1E-6,3,3,3,4,4*M_PI,6);

  //int len = end(planets)-begin(planets);

  float deltaT = 0.001;
  int N = 1500;
  string filename = "./data/test.txt";

  float Gconst = 4*M_PI*M_PI;

  diff_solver *test;
  test = new diff_solver(Gconst,n,planets);

  //solve(planets,len,deltaT,N,filename);

  delete[] *planets;

}
