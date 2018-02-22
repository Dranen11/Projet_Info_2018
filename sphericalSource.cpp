#include "sphericalSource.h"
#include <array>
#include <cmath>

using namespace std;

sphericalSource::sphericalSource(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, vecteur<double,3> luminosity, double radius)
    :celestialBody(mass, coordinate, speed), luminosity(luminosity), radius(radius), surface(4.*M_PI*pow(radius,3)/3.)
{

}

void sphericalSource::update_ray(ray& ray2update, celestialBody* next) const
{
    if((pow(ray2update.get_actualPos()[0]-coordinate[0],2.)+pow(ray2update.get_actualPos()[1]-coordinate[1],2.))<(radius*radius))
    {
        //ray2update.addLight(luminosity/(4.*M_PI*pow(ray2update.get_distance(),2.)));
        ray2update.addLight(luminosity);
    }
    if(next != NULL)
    {
        vecteur<double,3> newPos = ray2update.get_actualPos()-ray2update.get_previousPos();
        newPos *= (ray2update.get_previousPos()[2]-next->getCoordinate()[2])/newPos[2];
        newPos += ray2update.get_previousPos();
        ray2update.updateRay(newPos);
    }
}
