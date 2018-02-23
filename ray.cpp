#include "ray.h"
#include <limits>
#include <cmath>

using namespace std;

ray::ray(vecteur<double, 3> const& posSource, vecteur<double, 3> const& direction, std::vector<celestialBody*> const& objectList)
    :initPosSource(posSource), initDirection(direction), objectList(objectList), distance(0.), light({0.,0.,0.}), previousPos(posSource), actualPos({0.,0.,0.})
{

}

vecteur<double, 3> const& ray::get_initPosSource() const
{
    return initPosSource;
}

vecteur<double, 3> const& ray::get_initDirection() const
{
    return initDirection;
}

vecteur<double, 3> const& ray::get_actualPos() const
{
    return actualPos;
}

vecteur<double, 3> const& ray::get_previousPos() const
{
    return previousPos;
}

double ray::get_distance() const
{
    return distance;
}

void ray::updateRay(vecteur<double, 3> const& newPos)
{
    distance += (newPos-actualPos).norm();
    previousPos = actualPos;
    actualPos = newPos;
}

vecteur<double,3> ray::get_light() const
{
    return light;
}

void ray::addLight(vecteur<double,3> newLight)
{
    light += newLight;
}

vecteur<double,3> ray::calculateRay()
{
    light = vecteur<double,3>({0.,0.,0.});
    if(objectList.size()>0)
    {
        distance = 0.;
        previousPos = initPosSource;
        actualPos = previousPos+initDirection*(objectList[0]->getCoordinate()[2]-previousPos[2])/initDirection[2];

        for(size_t iter = 0; iter < (objectList.size()-1) && light.norm2() < std::numeric_limits<double>::min()*1.e6; iter++) //stop if there are any light, encounter as star
        {
            objectList[iter]->update_ray(*this,objectList[iter+1]);
        }
        if(light.norm2() < std::numeric_limits<double>::min()*1.e6) //update with the last celestialBody
        {
            objectList[(objectList.size()-1)]->update_ray(*this,NULL);
        }
    }
    return  light;
}
