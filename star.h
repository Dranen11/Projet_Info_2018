#ifndef STAR_H
#define STAR_H

#include "vecteur.h"
#include "sphericalSource.h"
#include "gravitationalLense.h"

//define a star with the luminosity is in function of a black body
class star : virtual public sphericalSource, virtual public gravitationalLense
{
public:
    star(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, double temperature, double radius); //all S.I. units
    virtual void update_ray(ray& ray2update, celestialBody* next) const;
    static vecteur<double,3> blackBodyLuminosity(double temperature, double radius);
};

#endif // STAR_H
