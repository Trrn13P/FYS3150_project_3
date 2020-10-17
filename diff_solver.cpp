#include "diff_solver.hpp"
#include "planet.h"

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;


void diff_solver::addPlanet(planet newplanet){
  planets[total_planets] = &newplanet;
  cout << planets[total_planets]->velocity[0] << endl;
  total_planets+=1;
  //cout << total_planets << endl;


}

mat diff_solver::diffEq(mat current_XV){

  /*
  planet *planets[4];
  planets[0] = new planet();
  planets[1] = new planet(3*1E-6,1,1,4,1,4*M_PI,5.5);
  planets[2] = new planet(3*1E-6,2,0.5,5,3,4*M_PI,5);
  planets[3] = new planet(3*1E-6,3,3,3,4,4*M_PI,6);
  //MIDLERTIDIG
  */
  mat dydt = zeros(n,6);
  /*
  for(int i=0;i<n;i++){
    for(int j=3;j<6;j++){
      dydt(i,j) = planets[i]->velocity[j-3];
    }
  }

  float Gconst = 4*M_PI*M_PI;
   //float Gconst = 6.67408*1E-11;

  for(int i=0;i<n;i++){
    vec a_i = zeros(3);
    vec r_i = zeros(3);
    vec r_j = zeros(3);
    vec r_ij = zeros(3); //unit ngth

    for(int k=0;k<3;k++){
      r_i[k] = planets[i]->position[k];
    }

    for(int j=0;j<n;j++){
      for(int k=0;k<3;k++){
        r_j[k] = planets[j]->position[k];
      }

      if(j!=i){
        r_ij = (r_j-r_i)*.1/norm(r_j-r_i,2);
        a_i = planets[i]->Acceleration(*planets[j],Gconst) * r_ij + a_i;
      }
    }
    for(int k=0;k<3;k++){
      dydt(i,k)=a_i(k);
    }
  }


  cout << dydt << endl;
  */
  return dydt;
}


void diff_solver::calcSlope(mat current_XV){



  mat k1 = diffEq(current_XV);
  //mat k2 = diffEq(current_XV+deltaT,n)
  cout << "calcSlope" << endl;
  //Bruker verlet osv. Gi positions videre(opdater klasse?)
  //diffEq(20);
}



void diff_solver::step(){
  mat current_XV = zeros(6,n);
  //Updating current position
  cout << planets[0]->position[1] << endl;
  /*
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      current_XV(i,j) = planets[i].velocity[j];
    }
    for(int j=3;j<n;j++){
      current_XV(i,j) = planets[i].position[j];
    }
  }
  calcSlope(current_XV);
  */
  //Update positions

}
