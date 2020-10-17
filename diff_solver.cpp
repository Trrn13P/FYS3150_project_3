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

void diff_solver::solve(float deltaT_, int N,string filename, string method_){
  method = method_;
  deltaT = deltaT_;
  ofstream outfile(filename);

  vec t = linspace(0,N*deltaT,N);
  outfile << "number_of_planets=" << n << " integration_points=" << N
  << " t:" << endl;
  outfile << t.t() << endl;

  mat current_XV = zeros(n,6);
  //Updating current position
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i]->position[j];
      current_XV(i,j+3) = planets[i]->velocity[j];
      }
    }

  outfile << current_XV << endl;

  for(int i=0;i<N;i++){
    mat new_XV = step(method);
    for(int i=0;i<n;i++){
      for(int j=0;j<3;j++){
        planets[i]->position[j] = new_XV(i,j);
        planets[i]->velocity[j] = new_XV(i,j+3);
      }
    }
    outfile << new_XV << endl;
  }
  outfile.close();
}
