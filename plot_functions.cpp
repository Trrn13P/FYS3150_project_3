#include <iostream>
#include <armadillo>
#include <fstream>
#include "planet.h"
#include "diff_solver.hpp"

float solar_mass(float mass){
  float mass_sun = 1.989*1E30;
  return mass*1./mass_sun;
}
float au_pr_yr(float pr_day){
  return pr_day*365.24;
}

void all_panets_plot(float Gconst, float beta, float deltaT, int T, string filename, string method, int saved_timesteps, bool relativistic_correction){
  int N = T*1./deltaT;

  string plot_type = "Orbits";
  int n = 13; //number of planets
  planet *planets[n];

    //PLANETS
    planets[0] = new planet(1,
    -6.005339779329579E-03,6.491104601150000E-03,8.587420750830977E-05,
    au_pr_yr(-7.374879897223016E-06),au_pr_yr(-4.969570018104684E-06),au_pr_yr(2.194527060357223E-07), "Sun");

    //planets[0] = new planet();

    //Mercury
    planets[1] = new planet(solar_mass(3.302*1E23),
    1.733524192276314E-01,-3.966245970437262E-01,-4.930765203822090E-02,
    au_pr_yr(2.006501659579929E-02),au_pr_yr(1.284256810042991E-02),au_pr_yr(-7.912123451233608E-04),"Mercury");

    //Venus
    planets[2] = new planet(solar_mass(4.867*1E24),
    5.990492016851071E-02, 7.234007276883858E-01, 6.120571140132686E-03,
    au_pr_yr(-2.021772814522031E-02), au_pr_yr(1.742186056797535E-03), au_pr_yr(1.190458772342569E-03), "Venus");

    //Earth
    planets[3] = new planet(solar_mass(5.972*1E24),
    9.826038297983306E-01, 1.626617426930922E-01, 7.845130873662143E-05,
    au_pr_yr(-2.970939298989496E-03), au_pr_yr(1.691727251702593E-02), au_pr_yr(-7.366459664051695E-07), "Earth");

    //Mars
    planets[4] = new planet(solar_mass(6.4171*1E23),
    1.360888014679430E+00, 3.349468216036287E-01, -2.656286033539554E-02,
    au_pr_yr(-2.740540234637191E-03), au_pr_yr(1.479651047448172E-02), 3.774487405860615E-04, "Mars");

    //Jupiter
    planets[5] = new planet(solar_mass(1.8982*1E27),
    2.465917496117004E+00, -4.485467614711858E+00, -3.656260354902041E-02,
    au_pr_yr(6.520238149039668E-03), au_pr_yr(3.993243263732226E-03), au_pr_yr(-1.624209573907791E-04), "Jupiter");

    //Saturn
    planets[6] = new planet(solar_mass(5.6846*1E26),
    5.081277066507966E+00, -8.603468928147084E+00, -5.269837833037497E-02,
    au_pr_yr(4.492276205657682E-03), au_pr_yr(2.822754464256181E-03), au_pr_yr(-2.280049094777040E-04), "Saturn");

    //Uranus
    planets[7] = new planet(solar_mass(8.681*1E25),
    1.556927665855843E+01, 1.220454655114423E+01, -1.563739043475883E-01,
    au_pr_yr(-2.455318794439842E-03), au_pr_yr(2.912147100528440E-03), au_pr_yr(4.262914105339306E-05), "Uranus");

    //Neptune
    planets[8] = new planet(solar_mass(1.0243*1E+26),
    2.940451628743331E+01, -5.508541430506357E+00, -5.642191373136077E-01,
    au_pr_yr(5.575570134307405E-04), au_pr_yr(3.103997180958646E-03), au_pr_yr(-7.714550346873532E-05), "Neptune");


    //Pluto
    planets[9] = new planet(solar_mass(1.303*1E+22),
    1.378644813583971E+01, -3.120757581440041E+01, -6.484604445330333E-01,
    au_pr_yr(2.944043168694716E-03), au_pr_yr(6.035872950584949E-04), au_pr_yr(-9.034499145666921E-04), "Pluto");


    //MOONS
    //Earth
    //Luna
    planets[10] = new planet(solar_mass(7.342*1E22),
    9.852601917937333E-01, 1.631441179955139E-01, -1.471816107151398E-04,
    au_pr_yr(-3.062651775167025E-03), au_pr_yr(1.747238423988413E-02), au_pr_yr(1.347558138998577E-05), "Luna");

    //Mars
    //Phobos
    planets[11] = new planet(solar_mass(1.0659*1E16),
    1.360843994161069E+00, 3.349073088946955E-01, -2.654211618170312E-02,
    au_pr_yr(-2.077812124315134E-03), au_pr_yr(1.382789210881808E-02), au_pr_yr(-4.954477391101918E-06), "Phobos");

    //Deimos
    planets[12] = new planet(solar_mass(1.4762*1E15),
    1.360825234055665E+00, 3.348040101616134E-01, -2.654667729259700E-02,
    au_pr_yr(-2.102186692109869E-03), au_pr_yr(1.447984598625061E-02), au_pr_yr(5.963423167754373E-05), "Deimos");

    diff_solver *all_planets;
    all_planets = new diff_solver(Gconst,beta,n,planets);
    all_planets->solve(deltaT,N,filename,method,plot_type,saved_timesteps, relativistic_correction);
    cout << all_planets->runtime << endl;
}

void check_runtime(float Gconst, float beta, int T, string filename, bool relativistic_correction){

  int n = 2; //number of planets
  planet *planets[n];

  float earth_over_sun = solar_mass(5.972*1E24);

  //PLANETS
  planets[0] = new planet(1,
  -earth_over_sun*earth_over_sun,0,0,
  0,-2*M_PI*earth_over_sun,0, "Sun");

  planets[1] = new planet(solar_mass(5.972*1E24),
  1, 0, 0,
  0, 2*M_PI, 0, "Earth");

  ofstream outfile(filename);
  outfile << "deltaT in yr, runtime in seconds" << endl;
  outfile << "deltaT: Euler: Euler-Cromer: Velocity-Verlet: RK4:" << endl;

  int N;
  string methods[] = {"Euler","Euler-Cromer","Velocity-Verlet", "RK4"};
  float deltaTs[] = {1E-1,1E-2,1E-3,1E-4,1E-5};
  string method;
  for(int j=0;j<5;j++){
    outfile << deltaTs[j];
    N = T*1./deltaTs[j];
    for(int i=0;i<4;i++){
      method = methods[i];
      diff_solver *earth_sun;
      earth_sun = new diff_solver(Gconst,beta,n,planets);
      earth_sun->solve_test(deltaTs[j],N,method, relativistic_correction);
      outfile << " "<< earth_sun->runtime;
  }
  outfile << "\n";
  }
  outfile.close();

}

void check_stability(float Gconst, float beta, int T, string filename, bool relativistic_correction){
  float earth_over_sun = solar_mass(5.972*1E24);

  int n = 2; //number of planets
  planet *planets[n];


  //PLANETS
  planets[0] = new planet(1,
  -earth_over_sun*earth_over_sun,0,0,
  0,-2*M_PI*earth_over_sun,0, "Sun");

  planets[1] = new planet(solar_mass(5.972*1E24),
  1, 0, 0,
  0, 2*M_PI, 0, "Earth");

  //Intital kinetic, potential and total energy for earth
  float k_0, u_0, initial_energy;
  k_0 = planets[1]->KineticEnergy();
  u_0 = planets[1]->PotentialEnergy(*planets[0],Gconst,0.0);
  initial_energy = k_0+u_0;

  //Final kinetic, potential and total energy for earth
  float k, u, final_energy;

  //Total energy intital and final for earth-sun
  float E_0_tot,E_tot;

  E_0_tot = planets[0]->KineticEnergy()
  +planets[1]->KineticEnergy()
  +planets[0]->PotentialEnergy(*planets[1],Gconst,0.0)
  +planets[1]->PotentialEnergy(*planets[0],Gconst,0.0);


  ofstream outfile(filename);
  outfile << "deltaT in yr, Total energy in Joules" << endl;
  outfile << "Initial K U E earth: " << k_0 << " " << u_0 << " " << initial_energy << endl;
  outfile << "Initial energy earth-sun: " << E_0_tot << endl;
  outfile << "K U e E_tot" << endl;
  outfile << "deltaT: Euler: Euler-Cromer: Velocity-Verlet: RK4:" << endl;


  int N;
  string methods[] = {"Euler","Euler-Cromer","Velocity-Verlet", "RK4"};
  float deltaTs[] = {1E-1,1E-2,1E-3,1E-4,1E-5};
  string method;
  for(int j=0;j<5;j++){
    outfile << deltaTs[j];
    N = T*1./deltaTs[j];
    for(int i=0;i<4;i++){
      method = methods[i];
      diff_solver *earth_sun;
      earth_sun = new diff_solver(Gconst,beta,n,planets);
      earth_sun->solve_test(deltaTs[j],N,method, relativistic_correction);

      k = planets[1]->KineticEnergy();
      u = planets[1]->PotentialEnergy(*planets[0],Gconst,0.0);
      final_energy = k+u;

      E_tot = planets[0]->KineticEnergy()
      +planets[1]->KineticEnergy()
      +planets[0]->PotentialEnergy(*planets[1],Gconst,0.0)
      +planets[1]->PotentialEnergy(*planets[0],Gconst,0.0);

      outfile << " "<< k << " "<< u << " "<< final_energy << " "<< E_tot;
  }
  outfile << "\n";
  }
  outfile.close();
}
