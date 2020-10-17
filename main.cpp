#include <iostream>
#include <armadillo>
#include "planet.h"
#include <fstream>

using namespace std;
using namespace arma;

mat diffEq(mat current_XV, planet *planets[], int n);
mat step(planet *planets[], int n,float deltaT);
void solve(planet *planets[], int n,float deltaT, int N,string filename);

int main(int argc, char const *argv[]) {
  planet *planets[2];
    planets[0] = new planet();
    planets[1] = new planet(3*1E-6,1,0,0,0,2*M_PI,0);
    //planets[2] = new planet(3*1E-6,2,0,0,4*M_PI,0,0);
    //planets[3] = new planet(3*1E-6,3,3,3,4,4*M_PI,6);

  int len = end(planets)-begin(planets);

  float deltaT = 0.001;
  int N = 15000;
  string filename = "./data/test.txt";

  solve(planets,len,deltaT,N,filename);

  delete[] *planets;

}

mat diffEq(mat current_XV, planet *planets[], int n){
  float Gconst = 4*M_PI*M_PI;
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
            r_ij = (r_i-r_j);
          }
        a_i = -Gconst * planets[j]->mass * 1/pow(norm(r_i-r_j),3) * r_ij + a_i;
      }

  }

  for(int k=0;k<3;k++){
    dydt(i,k+3)=a_i(k);
  }
}
  return dydt;
}



mat step(planet *planets[], int n,float deltaT){
  mat current_XV = zeros(n,6);
  //Updating current position
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i]->position[j];
      current_XV(i,j+3) = planets[i]->velocity[j];
      }
    }


    //Euler-Cromer

    mat next_XV = zeros(n,6);

    mat dydt_next = zeros(n,6);
    mat new_XV = zeros(n,6);

    mat dydt = diffEq(current_XV, planets, n);
    next_XV = dydt*deltaT + current_XV;
    dydt_next = diffEq(next_XV, planets, n);

    for(int i=0; i<n; i++){
      for(int j=0;j<3;j++){
        new_XV(i,j) = dydt_next(i,j)*deltaT+current_XV(i,j);
        new_XV(i,j+3) = dydt(i,j+3)*deltaT + current_XV(i,j+3);
      }
    }
    return new_XV;

    /*
    //Velocity-Verlet
    mat new_XV = zeros(n,6);

    mat dydt = diffEq(current_XV, planets, n);
    mat next_XV = dydt*deltaT + current_XV;

    mat dydt_next = diffEq(next_XV, planets, n);

    for(int i=0;i<n;i++){
      for(int j=0;j<3;j++){
        new_XV(i,j) =current_XV(i,j)+deltaT*dydt(i,j)+deltaT*deltaT/2*dydt(i,j+3);
        new_XV(i,j+3) = current_XV(i,j+3)+deltaT/2*(dydt_next(i,j+3)+dydt(i,j+3));
      }
    }
    return new_XV;
    */



    /*
    //Euler
    mat dydt = zeros(n,6);
    dydt = diffEq(current_XV, planets, n);
    current_XV + dydt*deltaT;
    */
    /*
    //RK4
    mat k1 = diffEq(current_XV, planets, n);
    mat k2 = diffEq(current_XV + k1*deltaT*1./2, planets, n);
    mat k3 = diffEq(current_XV+k2*deltaT*1./2, planets, n);
    mat k4 = diffEq(current_XV+k3*deltaT, planets, n);
    dydt = (k1 + 2*k2 + 2*k3 + k4)/6;
    return current_XV + dydt*deltaT;
    */




}

void solve(planet *planets[], int n,float deltaT, int N,string filename){
  ofstream outfile(filename);

  vec t = linspace(0,N*deltaT,N);
  outfile << "number_of_planets=" << n << " t:" << endl;
  outfile << t.t() << endl;

  mat current_XV = zeros(n,6);
  //Updating current position
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i]->position[j];
      current_XV(i,j+3) = planets[i]->velocity[j];
      }
    }

  //outfile << current_XV << endl;

  for(int i=0;i<N;i++){
    mat new_XV = step(planets,n,deltaT);
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
