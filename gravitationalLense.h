#ifndef GRAVITATIONALLENSE_H
#define GRAVITATIONALLENSE_H

#include "celestialBody.h"

class gravitationalLense : public celestialBody
{
public:
    gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed);

    virtual void update_ray(ray& ray2update) const;
};

#endif // GRAVITATIONALLENSE_H
