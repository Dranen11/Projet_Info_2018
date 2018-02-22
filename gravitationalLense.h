#ifndef GRAVITATIONALLENSE_H
#define GRAVITATIONALLENSE_H

#include "celestialBody.h"

#define C_G 6.67408e-11
#define C_C 299792458.
#define C_H 6.62606957e-34
#define C_Kb 1.3806488e-23



class gravitationalLense : virtual public celestialBody
{
public:
    gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed);

    virtual void update_ray(ray& ray2update, celestialBody* next) const;
};

#endif // GRAVITATIONALLENSE_H
