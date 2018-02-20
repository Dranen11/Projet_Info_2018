#include "ray.h"
#include <limits>
#include <cmath>

using namespace std;

ray::ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction)
    :posSource(posSource), direction(direction), distance(0.), dirChangeLU(true), light({0.,0.,0.})
{

}

ray::ray()
    :posSource({0.,0.,0.}), direction({0.,0.,0.}), distance(0.), dirChangeLU(true), light({0.,0.,0.})
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

vecteur<double,3> ray::get_light() const
{
    return light;
}

void ray::addLight(vecteur<double,3> newLight)
{
    light += newLight;
}

vecteur<double,3> ray::calculateRay(std::vector<celestialBody*> objectList, std::size_t maxIter)
{
    std::vector<bool> valid(objectList.size(),true);
    std::size_t iter=0, localIter = 0;
    dirChangeLU = false;

    sortObjectList(objectList, valid, NULL);

    while(localIter < objectList.size() && iter < maxIter && light.norm2() < std::numeric_limits<double>::min()*10.)
    {
        if(dirChangeLU)
        {
            localIter = 0;
            sortObjectList(objectList, valid, objectList[localIter]);
            dirChangeLU = false;
        }

        if(valid[localIter])
        {
            objectList[localIter]->update_ray(*this);
        }
        iter++; localIter++;

    }
    return light;
}

double ray::intersectPlane(vecteur<double,3> const& normal) const
{
    double normalNorm = normal.norm(), denom = vecteur<double,3>::scalarProduct(direction,normal)/normalNorm, distIntersect = -1.;
    if(abs(denom) > std::numeric_limits<double>::min()*1.e30) {
        distIntersect = normalNorm/denom;
    }
    return distIntersect;
}

void ray::sortObjectList(std::vector<celestialBody*>& objectList, std::vector<bool>& valid, celestialBody* last)
{
    std::vector<double> distance(objectList.size(),0.);
    bool first = true;

    for(size_t i = 0; i < objectList.size(); i++)
    {
        distance[i] = intersectPlane(objectList[i]->getCoordinate()-posSource);
    }

    for(size_t i = 0; i<objectList.size();i++)
    {
        for(size_t j = 0; j <(objectList.size()-i-1); j++)
        {
            if(distance[j]>distance[j+1])
            {
                std::swap<double>(distance[j],distance[j+1]);
                std::swap<celestialBody*>(objectList[j],objectList[j+1]);
            }
        }
    }
    for(size_t i = 0; i < objectList.size(); i++)
    {
        valid[i] = (distance[i] > 0.);
        if(first && distance[i] > 0.) {
            if(objectList[i] == last)
            {
                valid[i] = false;
            }
            first = false;
        }
    }
}
