#include "pixel.h"
#include <algorithm>

using namespace std;

pixel::pixel(ray const& r1, ray const& r2)
    :r1(r1), r2(r2), initR1(r1), initR2(r2)
{

}

pixel::pixel()
{

}

void pixel::set_initR1(ray const& newRay)
{
    initR1 = newRay;
}

void pixel::set_initR2(ray const& newRay)
{
    initR2 = newRay;
}

ray pixel::get_initR1() const
{
    return initR1;
}

ray pixel::get_initR2() const
{
    return initR2;
}

ray const& pixel::get_r1() const
{
    return r1;
}

ray const& pixel::get_r2() const
{
    return r2;
}

ray& pixel::get_r1()
{
    return r1;
}

ray& pixel::get_r2()
{
    return r2;
}

vecteur<double,3> pixel::get_light() const
{
    return light;
}

bool pixel::getBlocked() const
{
    return blocked;
}

void pixel::addLight(vecteur<double,3> newLight)
{
    light += newLight;
}

void pixel::Blocked()
{
    blocked = true;
}

void pixel::calculatePixel(std::vector<celestialBody const *> objectList, std::size_t maxIter)
{
    std::vector<bool> valid(objectList.size(),true);
    light = vecteur<double,3>({0.,0.,0.});
    std::size_t iter=0, localIter = 0;
    blocked = false;
    r1 = initR1;
    r2 = initR2;

    sortObjectList(objectList, valid, NULL);
    r1.updateRay();
    r2.updateRay();

    while(localIter < objectList.size() && iter < maxIter && (!blocked))
    {
        if(r1.get_dirChangeLU() || r2.get_dirChangeLU())
        {
            localIter = 0;
            sortObjectList(objectList, valid, objectList[localIter]);
            r1.updateRay();
            r2.updateRay();
        }

        if(valid[localIter])
        {
            objectList[localIter]->update_pixel(*this);
        }
        iter++; localIter++;
    }
}

void pixel::sortObjectList(std::vector<const celestialBody*>& objectList, std::vector<bool>& valid, celestialBody const * last)
{
    vecteur<double, 3> meanPosition = (r1.get_posSource()+r2.get_posSource())*0.5;
    vecteur<double, 3> meanDirection = (r1.get_direction()+r2.get_direction())*0.5;
    std::vector<double> distance(objectList.size(),0.);

    for(size_t i = 0; i < objectList.size(); i++)
    {
        distance[i] = (meanPosition-objectList[i]->getCoordinate()).norm();
    }

    for(size_t i = 0; i<objectList.size();i++)
    {
        for(size_t j = 0; j <(objectList.size()-i-1); j++)
        {
            if(distance[j]>distance[j+1])
            {
                std::swap<double>(distance[j],distance[j+1]);
                std::swap<const celestialBody*>(objectList[j],objectList[j+1]);
            }
        }
    }
    for(size_t i = 0; i < objectList.size(); i++)
    {
        valid[i] = (vecteur<double,3>::scalarProduct(objectList[i]->getCoordinate(),meanDirection) > 0.);
    }
    if(objectList[0] == last)
    {
        valid[0] = false;
    }
}
