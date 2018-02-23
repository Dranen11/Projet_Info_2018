#ifndef RAY_H
#define RAY_H

#include <vector>
#include "vecteur.h"
#include "celestialBody.h"

class celestialBody;

//define a ray of light
class ray
{
public:
    ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction, std::vector<celestialBody*> const& objectList);

    vecteur<double, 3> const& get_initPosSource() const;
    vecteur<double, 3> const& get_initDirection() const;
    vecteur<double, 3> const& get_actualPos() const;
    vecteur<double, 3> const& get_previousPos() const;
    double get_distance() const;
    void addLight(vecteur<double,3> newLight);
    vecteur<double,3> get_light() const;

    void updateRay(vecteur<double, 3> const& newPos);
    vecteur<double,3> calculateRay();


protected:

    double distance;
    std::vector<celestialBody*> const& objectList;
    vecteur<double, 3> previousPos;
    vecteur<double, 3> actualPos;
    vecteur<double, 3> initPosSource;
    vecteur<double, 3> initDirection;
    vecteur<double, 3> light;
};

#endif // RAY_H
