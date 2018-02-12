#ifndef SPHERICALSOURCE_H
#define SPHERICALSOURCE_H

#include "vecteur.h"
#include "celestialBody.h"

class sphericalSource : public celestialBody
{
public:
    sphericalSource(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, vecteur<double,3> luminosity, double radius);

    virtual void update_pixel(pixel& pixel2update) const;

protected:
    vecteur<double,3> luminosity;
    double radius, surface;
};

#endif // SPHERICALSOURCE_H
