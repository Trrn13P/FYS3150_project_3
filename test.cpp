#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <cmath>
#include <iostream>
#include "diff_solver.hpp"
#include "planet.h"
#include <armadillo>

using namespace std;

TEST_CASE("ENERGY_CONSERVED"){
  int n = 2; //number of planets
  float earth_over_sun = 3.0025*1E-6;
  float Gconst = 4*M_PI*M_PI;
  float beta = 2;

  float deltaT = 1E-5;
  float T = 1;
  float N = T/deltaT;
  bool relativistic_correction = false;
  string method = "Velocity-Verlet";



  planet *planets[n];

  planets[0] = new planet(1,
  -earth_over_sun*earth_over_sun,0,0,
  0,-2*M_PI*earth_over_sun,0, "Sun");

  planets[1] = new planet(earth_over_sun,
  1, 0, 0,
  0, 2*M_PI,0 , "Earth");

  float energy_before, energy_after, kinetic_energy, potential_energy;
  kinetic_energy = planets[0]->KineticEnergy();
  kinetic_energy+= planets[1]->KineticEnergy();

  potential_energy = planets[0]->PotentialEnergy(*planets[1],Gconst,0.0);
  potential_energy += planets[1]->PotentialEnergy(*planets[0],Gconst,0.0);


  energy_before = kinetic_energy+potential_energy;


  vec velocity_1 = zeros(3);
  vec velocity_2 = zeros(3);
  vec r_1 = zeros(3);
  vec r_2 = zeros(3);
  float l1_before, l2_before, l1_after, l2_after;

  for(int i=0;i<3;i++){
    r_1[i] = planets[0]->position[i];
    r_2[i] = planets[1]->position[i];

    velocity_1[i] = planets[0]->velocity[i];
    velocity_2[i] = planets[1]->velocity[i];
  }
  l1_before = norm(cross(r_1,velocity_1));
  l2_before = norm(cross(r_2,velocity_2));

  diff_solver *earth_sun;
  earth_sun = new diff_solver(Gconst,beta,n,planets);
  energy_after = earth_sun->solve_test(deltaT,N,method, relativistic_correction);

  for(int i=0;i<3;i++){
    r_1[i] = planets[0]->position[i];
    r_2[i] = planets[1]->position[i];

    velocity_1[i] = planets[0]->velocity[i];
    velocity_2[i] = planets[1]->velocity[i];
  }
  l1_after = norm(cross(r_1,velocity_1));
  l2_after = norm(cross(r_2,velocity_2));


  REQUIRE(energy_before==Approx(energy_after).epsilon(0.0001));
  REQUIRE(l1_before==Approx(l1_after).epsilon(0.0001));
  REQUIRE(l2_before==Approx(l2_after).epsilon(0.0001));
}
