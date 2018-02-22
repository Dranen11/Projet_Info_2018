#include "gravitationalLense.h"
#include <cmath>

#define M_G 6.67408e-11
#define M_C 299792458.


using namespace std;


gravitationalLense::gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed)
    :celestialBody(mass,coordinate,speed)
{

}

void gravitationalLense::update_ray(ray& ray2update, celestialBody* next) const
{
    if(next != NULL)
    {
        double distance2Lense = sqrt(pow(ray2update.get_actualPos()[0]-coordinate[0],2.)+pow(ray2update.get_actualPos()[1]-coordinate[1],2.));
        double deviationAngle = 4.*M_G*mass/(distance2Lense*M_C*M_C);
        double deviationAngleX = deviationAngle*(ray2update.get_actualPos()[0]-coordinate[0])/distance2Lense;
        double deviationAngleY = deviationAngle*(ray2update.get_actualPos()[1]-coordinate[1])/distance2Lense;

        vecteur<double,3> newPos = ray2update.get_actualPos()-ray2update.get_previousPos();
        newPos *= (ray2update.get_previousPos()[2]-next->getCoordinate()[2])/newPos[2];
        newPos += ray2update.get_previousPos();
        newPos[0] -= deviationAngleX*(newPos[2]-ray2update.get_actualPos()[2]);
        newPos[1] -= deviationAngleY*(newPos[2]-ray2update.get_actualPos()[2]);

        ray2update.updateRay(newPos);
    }
}
