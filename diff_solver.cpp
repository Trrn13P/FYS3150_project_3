#include <iostream>
#include <armadillo>
#include <fstream>

#include "planet.h"
#include "diff_solver.hpp"

using namespace std;
using namespace arma;

mat diff_solver::diffEq(mat current_XV){
  mat dydt = zeros(n,6);
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      dydt(i,j) = current_XV(i,j+3);
    }
}

  for(int i=0;i<n;i++){
    vec a_i = zeros(3); //Acceleration for planet i
    vec r_i = zeros(3); //Vector from Origo to planet i
    vec r_j = zeros(3); //Vector from Origo to planet j
    vec r_ij = zeros(3); //Vector from planet i to planet j

    for(int k=0;k<3;k++){
        r_i[k] = current_XV(i,k);
      }
      for(int j=0;j<n;j++){

        for(int k=0;k<3;k++){
          r_j[k] = current_XV(j,k);
        }

        if(j!=i){
          if(norm(r_j-r_i,2)==0){
            r_ij = zeros(3);
          }
          else{
            r_ij = (r_i-r_j)*1/norm(r_i-r_j,2);
          }
        a_i = -Gconst * planets[j]->mass * 1/powf(norm(r_i-r_j),beta) * r_ij + a_i;
      }

  }

  for(int k=0;k<3;k++){
    dydt(i,k+3)=a_i(k);
  }
}
  return dydt;
}



mat diff_solver::step(string method_){
  mat current_XV = zeros(n,6);
  //Updating current position
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i]->position[j];
      current_XV(i,j+3) = planets[i]->velocity[j];
      }
    }

    if(method=="Euler"){
      //Euler
      mat dydt = zeros(n,6);
      dydt = diffEq(current_XV);
      return current_XV + dydt*deltaT;
      }

    if(method=="Euler-Cromer"){
      //Euler-Cromer
      mat next_XV = zeros(n,6);

      mat dydt_next = zeros(n,6);
      mat new_XV = zeros(n,6);

      mat dydt = diffEq(current_XV);
      next_XV = dydt*deltaT + current_XV;
      dydt_next = diffEq(next_XV);

      for(int i=0; i<n; i++){
        for(int j=0;j<3;j++){
          new_XV(i,j) = dydt_next(i,j)*deltaT+current_XV(i,j);
          new_XV(i,j+3) = dydt(i,j+3)*deltaT + current_XV(i,j+3);
        }
      }
    return new_XV;
    }

    if(method=="Velocity-Verlet"){

    //Velocity-Verlet
    mat new_XV = zeros(n,6);

    mat dydt = diffEq(current_XV);
    mat next_XV = dydt*deltaT + current_XV;

    mat dydt_next = diffEq(next_XV);

    for(int i=0;i<n;i++){
      for(int j=0;j<3;j++){
        new_XV(i,j) =current_XV(i,j)+deltaT*dydt(i,j)+deltaT*deltaT/2*dydt(i,j+3);
        new_XV(i,j+3) = current_XV(i,j+3)+deltaT/2*(dydt_next(i,j+3)+dydt(i,j+3));
      }
    }
    return new_XV;
  }





    if(method=="RK4"){
    //RK4
    mat k1 = diffEq(current_XV);
    mat k2 = diffEq(current_XV + k1*deltaT*1./2);
    mat k3 = diffEq(current_XV+k2*deltaT*1./2);
    mat k4 = diffEq(current_XV+k3*deltaT);
    mat dydt = (k1 + 2*k2 + 2*k3 + k4)/6;
    return current_XV + dydt*deltaT;
  }

  else{
    if(error_message==1){
      error_message=0;
      cout << "No method found, returning zeros." << endl;
    }

    return zeros(n,6);
  }



}

void diff_solver::solve(float deltaT_, int N,string filename, string method_, string plot_type, int step_saved){
  method = method_;
  deltaT = deltaT_;
  vec t = linspace(0,N*deltaT,N);

  mat current_XV = zeros(n,6);
  //Updating current position
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i]->position[j];
      current_XV(i,j+3) = planets[i]->velocity[j];
      }
    }




  ofstream outfile(filename);
  int k = 0;

  if(plot_type=="Total_Energy"){
    float kinetic_energy, potential_energy, total_energy;
    outfile << "number_of_planets=" << n << " integration_points=" << N
    << " method=" << method << endl;
    outfile << "t: Total Energy:" << endl;
    for(int steps=0;steps<N;steps++){
      total_energy = 0;
      kinetic_energy = 0;
      potential_energy = 0;

      for(int i=0;i<n;i++){
        for(int k=0;k<n;k++){
          if(i!=k){
            potential_energy+=planets[i]->PotentialEnergy(*planets[k],Gconst,0.0);
          }
        }
        kinetic_energy += planets[i]->KineticEnergy();
      }
      total_energy = kinetic_energy+potential_energy;

      //TOTAL ENERGY =SUM(KINETIC ENERGY+ SUM POTENTIAL)
      outfile << t(steps) << " " << total_energy << endl;

      mat new_XV = step(method);
      for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
          planets[i]->position[j] = new_XV(i,j);
          planets[i]->velocity[j] = new_XV(i,j+3);
        }

      }


    }
    outfile.close();
  }


  int timesteps_pr_year = 1./deltaT;
  int interval, points_saved;
  if(step_saved>timesteps_pr_year){
    interval = 1;
    points_saved = N;
  }
  else{
    interval = timesteps_pr_year*1./step_saved;
    points_saved = step_saved*1./timesteps_pr_year * N;
  }




  if(plot_type=="Orbits"){
    outfile << "number_of_planets=" << n << " points_saved=" << points_saved <<
    " method=" << method << " t:" << endl;
    outfile << t.t() << endl;
    outfile << current_XV << endl;

    for(int steps=0;steps<N;steps++){
      mat new_XV = step(method);
      for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
          planets[i]->position[j] = new_XV(i,j);
          planets[i]->velocity[j] = new_XV(i,j+3);
        }
      }
      k+=1;
        if(k>=interval){
          outfile << new_XV << endl;
          k=0;
        }


    }
    outfile.close();
  }
}
