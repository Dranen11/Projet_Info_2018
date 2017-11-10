#ifndef RAY_H
#define RAY_H

#include "vecteur.h"


class ray
{
public:
    ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction);

    vecteur<double, 3> const& get_posSource() const;
    vecteur<double, 3> const& get_direction() const;
    bool get_dirChangeLU() const;
    double get_distance() const;

    void updateRay(vecteur<double, 3> const& new_posSource, vecteur<double, 3> const& new_direction);
    void updateRay();

protected:
    bool dirChangeLU;
    double distance;
    vecteur<double, 3> posSource;
    vecteur<double, 3> direction;
};

#endif // RAY_H
