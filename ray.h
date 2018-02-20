#ifndef RAY_H
#define RAY_H

#include <vector>
#include "vecteur.h"
#include "celestialBody.h"

class celestialBody;

class ray
{
public:
    ray();
    ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction);

    vecteur<double, 3> const& get_posSource() const;
    vecteur<double, 3> const& get_direction() const;
    bool get_dirChangeLU() const;
    double get_distance() const;
    void addLight(vecteur<double,3> newLight);
    vecteur<double,3> get_light() const;

    void updateRay(vecteur<double, 3> const& new_posSource, vecteur<double, 3> const& new_direction);
    void updateRay();
    vecteur<double,3> calculateRay(std::vector<celestialBody*> objectList, std::size_t maxIter = 100);


protected:
    void sortObjectList(std::vector<celestialBody*>& objectList, std::vector<bool>& valid, celestialBody* last);
    double intersectPlane(vecteur<double,3> const& normal) const;

    bool dirChangeLU;
    double distance;
    vecteur<double, 3> posSource;
    vecteur<double, 3> direction;
    vecteur<double, 3> light;
};

#endif // RAY_H
