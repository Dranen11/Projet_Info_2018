#include "observer.h"
#include <cmath>
#include <omp.h>


using namespace std;

Observer::Observer(vecteur<double, 3> pointingVector, double fov, std::array<uint32_t,2> resolution, size_t subSampling)
    :pointingVector(pointingVector), fov(fov), resolution(resolution), isUpdate(false), subSampling(max(static_cast<size_t>(1),subSampling))
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
    //if image is not up to date calculate it
    if(!isUpdate)
    {
        calculateImage();
    }
    return image;
}

void Observer::calculateImage()
{

    vecteur<double,3> posSource({0,0,0}), nullVecteur({0.,0.,0.});
    //value for determining a ray for a pixel
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

    //value for determing ray in the subsample case
    double samplingParity = 1.-static_cast<double>(subSampling % 2);
    double sampling_half = static_cast<double>(subSampling/2);
    double xSamplingAngleRes = xAngleRes/static_cast<double>(subSampling);
    double ySamplingAngleRes = yAngleRes/static_cast<double>(subSampling);


    #pragma omp parallel for num_threads(omp_get_max_threads()) schedule(dynamic,2)
    for(size_t i = 0; i < resolution[0]; i++)
    {
        for(size_t j = 0; j < resolution[1]; j++)
        {
            if(subSampling > 1) // if subsampling is activate
            {
                array<double,3> aDir = aPointer;
                aDir[2] += yAngleRes*(static_cast<double>(j)-ny_half+0.5*yparity);
                aDir[1] += xAngleRes*(static_cast<double>(i)-nx_half+0.5*xparity);
                image[i][j]= nullVecteur;

                for(size_t k = 0; k < subSampling; k++)
                {
                    for(size_t l = 0; l < subSampling; l++)
                    {
                        array<double,3> aDirSample = aDir;
                        aDirSample[2] += ySamplingAngleRes*(static_cast<double>(l)-sampling_half+0.5*samplingParity);;
                        aDirSample[1] += xSamplingAngleRes*(static_cast<double>(k)-sampling_half+0.5*samplingParity);;
                        ray lauchedRay(posSource,vecteur<double,3>::createFromAngularCoordinate(aDirSample),objectList);
                        image[i][j] += lauchedRay.calculateRay();
                    }
                }
            }
            else
            {
                array<double,3> aDir = aPointer;
                aDir[2] += yAngleRes*(static_cast<double>(j)-ny_half+0.5*yparity);
                aDir[1] += xAngleRes*(static_cast<double>(i)-nx_half+0.5*xparity);
                ray lauchedRay(posSource,vecteur<double,3>::createFromAngularCoordinate(aDir),objectList);
                image[i][j] = lauchedRay.calculateRay();
            }
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

void Observer::set_subSampling(size_t newSubSampling)
{
    if(subSampling != newSubSampling)
    {
        subSampling = max(static_cast<size_t>(1),newSubSampling);
        isUpdate = false;
    }
}


size_t Observer::get_subsampling() const
{
    return subSampling;
}
