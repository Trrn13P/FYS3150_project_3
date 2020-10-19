#ifndef PLANET_H
#define PLANET_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include <iostream>
using std::vector;

class planet
{

public:

    // Properties
    double mass;
    double position[3];
    double velocity[3];
    double potential;
    double kinetic;
    std::string planet_name;

    // Initializers
    planet();
    planet(double M,double x,double y,double z,double vx, double vy,double vz, std::string planet_name_);

    // Functions
    double distance(planet otherPlanet);
    double GravitationalForce(planet otherPlanet, double Gconst);
    double Acceleration(planet otherPlanet, double Gconst);
    double KineticEnergy();
    double PotentialEnergy(planet &otherPlanet, double Gconst, double epsilon);

};

#endif // PLANET_H
