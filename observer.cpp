#include "observer.h"
#include <cmath>

using namespace std;

Observer::Observer(vecteur<double, 3> pointingVector, double fov, std::array<uint32_t,2> resolution)
    :pointingVector(pointingVector), fov(fov), resolution(resolution), isUpdate(false)
{
    newResolution();
}

void Observer::set_objectList(std::vector<celestialBody*> const& newObjectList)
{
    isUpdate = false;
    objectList = newObjectList;
    sortObjectList();
}

std::vector<celestialBody*> Observer::get_objectList() const
{
    return objectList;
}

void Observer::set_pointingVector(vecteur<double, 3> const& newVector)
{
    pointingVector = newVector;
    isUpdate = false;
}

vecteur<double, 3> Observer::get_pointingVector() const
{
    return pointingVector;
}

std::array<uint32_t,2> Observer::get_resolution() const
{
    return resolution;
}

void Observer::set_resolution(std::array<uint32_t,2> const& newRes)
{
    resolution = newRes;
    newResolution();
}

double Observer::get_fov() const
{
    return fov;
}

void Observer::set_fov(double newFOV)
{
    fov = newFOV;
    isUpdate = false;
}

std::vector<std::vector<vecteur<double,3>>> Observer::getImage()
{
    if(!isUpdate)
    {
        calculateImage();
    }
    return image;
}

void Observer::calculateImage()
{

    vecteur<double,3> posSource({0,0,0});
    array<double,3> aPointer = pointingVector.getAngularCoordinate();
    double xparity = 1.-static_cast<double>(resolution[0] % 2);
    double yparity = 1.-static_cast<double>(resolution[1] % 2);
    double nx_half = static_cast<double>(resolution[0]/2);
    double ny_half = static_cast<double>(resolution[1]/2);
    double ratio = static_cast<double>(resolution[1])/static_cast<double>(resolution[0]);
    double yFov = sqrt(fov*fov/(ratio*ratio+1));
    double xFov = yFov*ratio;
    double xAngleRes = xFov/static_cast<double>(resolution[0]);
    double yAngleRes = yFov/static_cast<double>(resolution[1]);

    for(size_t i = 0; i < resolution[0]; i++)
    {
        for(size_t j = 0; j < resolution[1]; j++)
        {
            array<double,3> aDir = aPointer;
            aDir[1] += yAngleRes*(static_cast<double>(j)-ny_half+0.5*yparity);
            aDir[2] += xAngleRes*(static_cast<double>(i)-nx_half+0.5*xparity);
            ray lauchedRay(posSource,vecteur<double,3>::createFromAngularCoordinate(aDir),objectList);
            image[i][j] = lauchedRay.calculateRay();
        }
    }
}

void Observer::newResolution()
{
    image.resize(resolution[0]);
    for(size_t i = 0; i<resolution[0];i++)
    {
        image[i].resize(resolution[1]);
    }
    isUpdate = false;
}

void Observer::testUpdate()
{
    for(size_t i = 0; i < objectList.size(); i++)
    {
        isUpdate = isUpdate && !(objectList[i]->get_hasChange());
    }
}

void Observer::sortObjectList()
{
    for(size_t i = 0; i<objectList.size();i++)
    {
        for(size_t j = 0; j <(objectList.size()-i-1); j++)
        {
            if(objectList[j]->getCoordinate()[2] >objectList[j+1]->getCoordinate()[2])
            {
                std::swap<celestialBody*>(objectList[j],objectList[j+1]);
            }
        }
    }
}
