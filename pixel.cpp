#include "pixel.h"
#include <algorithm>

using namespace std;

pixel::pixel(ray r1, ray r2)
    :r1(r1), r2(r2)
{

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
    std::size_t iter=0, localIter = 0;

    sortObjectList(objectList);
    r1.updateRay();
    r2.updateRay();

    while(localIter < objectList.size() && iter < maxIter)
    {
        if(r1.get_dirChangeLU() || r2.get_dirChangeLU())
        {
            localIter = 0;
            sortObjectList(objectList);
            r1.updateRay();
            r2.updateRay();
        }

        objectList[localIter]->update_pixel(*this);

        iter++; localIter++;
    }
}

void pixel::sortObjectList(std::vector<const celestialBody*>& objectList)
{
    vecteur<double, 3> meanPosition = (r1.get_posSource()+r2.get_posSource())*0.5;
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
}
