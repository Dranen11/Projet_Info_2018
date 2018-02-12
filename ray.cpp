#include "ray.h"

ray::ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction)
    :posSource(posSource), direction(direction), distance(0.), dirChangeLU(true)
{

}

ray::ray()
    :posSource({0.,0.,0.}), direction({0.,0.,0.}), distance(0.), dirChangeLU(true)
{

}

vecteur<double, 3> const& ray::get_posSource() const
{
    return posSource;
}

vecteur<double, 3> const& ray::get_direction() const
{
    return direction;
}

bool ray::get_dirChangeLU() const
{
    return dirChangeLU;
}

double ray::get_distance() const
{
    return distance;
}

void ray::updateRay(vecteur<double, 3> const& new_posSource, vecteur<double, 3> const& new_direction)
{
    distance += (posSource-new_posSource).norm();
    posSource = new_posSource;
    direction = new_direction;
    dirChangeLU = true;
}

void ray::updateRay()
{
    dirChangeLU = false;
}
