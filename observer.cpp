#include "observer.h"

using namespace std;

Observer::Observer(vecteur<double, 3> pointingVector, double fov, std::array<double,2> resolution)
    :pointingVector(pointingVector), fov(fov), resolution(resolution), isUpdate(false), maxIterImage(100)
{
    newResolution();
}

void Observer::set_objectList(std::vector<celestialBody const *> const& newObjectList)
{
    isUpdate = false;
    objectList = newObjectList;
}

std::vector<celestialBody const *> Observer::get_objectList() const
{
    return objectList;
}

void Observer::set_pointingVector(vecteur<double, 3> const& newVector)
{
    pointingVector = newVector;
    changeView();
}

vecteur<double, 3> Observer::get_pointingVector() const
{
    return pointingVector;
}

std::array<double,2> Observer::get_resolution() const
{
    return resolution;
}

void Observer::set_resolution(std::array<double,2> const& newResolution)
{
    resolution = newResolution;
    newResolution();
}

double Observer::get_fov() const
{
    return fov;
}

void Observer::set_fov(double newFOV)
{
    fov = newFOV;
    changeView();
}

size_t Observer::get_maxIterImage() const
{
    return maxIterImage;
}

void Observer::set_maxIterImage(size_t maxIter)
{
    maxIterImage = maxIter;
}

std::vector<std::vector<vecteur<double,3>>> Observer::getImage()
{
    if(!isUpdate || resChange)
    {
        calculateImage();
    }
    return image;
}

void Observer::calculateImage()
{
    for(size_t i = 0; i < resolution[0]; i++)
    {
        for(size_t j = 0; j < resolution[1]; j++)
        {
            generatingImage[i][j].calculatePixel(objectList,maxIterImage);
            image[i][j] = generatingImage[i][j].get_light();
        }
    }
}

void Observer::newResolution()
{
    generatingImage.resize(resolution[0]);
    image.resize(resolution[0]);
    for(size_t i = 0; i<resolution[0];i++)
    {
        generatingImage[i].resize(resolution[1]);
        image[i].resize(resolution[1]);
    }
    changeView();
    isUpdate = false;
}

void Observer::changeView()
{
    vecteur<double,3> posSource = {0,0,0}, dir1, dir2;
    array<double,3> aDir1, aDir2, aDirPixel, aPointer == pointingVector.getPolarCoordinate();
    double xparity = 1.-static_cast<double>(resolution[0] % 2);
    double yparity = 1.-static_cast<double>(resolution[1] % 2);
    double nx_half = static_cast<double>(resolution[0]/2);
    double ny_half = static_cast<double>(resolution[1]/2);
    double xAngleRes = fov/static_cast<double>(resolution[0]);
    double yAngleRes = fov/static_cast<double>(resolution[1]);

    for(size_t i = 0; i < resolution[0]; i++)
    {
        for(size_t j = 0; j < resolution[1]; j++)
        {
            aDirPixel = aPointer;
            aDirPixel[1] += yAngleRes*(static_cast<double>(j)-ny_half+0.5*yparity);
            aDirPixel[2] += xAngleRes*(static_cast<double>(i)-nx_half+0.5*xparity);

            aDir1 = aDirPixel;
            aDir2 = aDirPixel;

            aDir1[1] -= 0.5*yAngleRes;
            aDir2[1] += 0.5*yAngleRes;
            aDir1[2] -= 0.5*xAngleRes;
            aDir2[2] += 0.5*xAngleRes;

            dir1.setPolarCoordinate(aDir1);
            dir2.setPolarCoordinate(aDir2);

            generatingImage[i][j].set_initR1(ray(posSource,dir1));
            generatingImage[i][j].set_initR2(ray(posSource,dir2));
        }
    }
    isUpdate = false;
}

void Observer::testUpdate()
{
    for(size_t i = 0; i < objectList.size(); i++)
    {
        isUpdate = isUpdate || !(objectList[i].get_hasChange());
    }
}
