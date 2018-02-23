#ifndef GRAVITATIONALLENSE_H
#define GRAVITATIONALLENSE_H

#include "celestialBody.h"


//define a graviational lense
class gravitationalLense : virtual public celestialBody
{
public:
    gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed);

    virtual void update_ray(ray& ray2update, celestialBody* next) const;
};

#endif // GRAVITATIONALLENSE_H
