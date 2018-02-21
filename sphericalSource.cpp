#include "sphericalSource.h"
#include <array>
#include <cmath>

#include <QtCore>
#include <QObject>

using namespace std;

sphericalSource::sphericalSource(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, vecteur<double,3> luminosity, double radius)
    :celestialBody(mass, coordinate, speed), luminosity(luminosity), radius(radius), surface(4.*M_PI*pow(radius,3)/3.)
{

}

void sphericalSource::update_ray(ray& ray2update) const
{
    vecteur<double,3> cpCoordinate = coordinate;
    vecteur<double,3> dirSource = coordinate-ray2update.get_posSource(), dirR = ray2update.get_direction();

    array<vecteur<double,3>,3> newBase; //base de la lentille
    newBase[2] = dirSource; //vecteur z dans la base de la lentille correspondant à l'axe source, lentille
    double distanceFromSource =  newBase[2].norm(); //distance lentille source
    newBase[2] /= distanceFromSource;

    if(abs(newBase[2][2])>0.01)
    {
        newBase[1][1] = 1.;
        newBase[1][0] = 0.;
        newBase[1][2] = -newBase[2][1]/newBase[2][2];
        newBase[1] /= newBase[1].norm();
    }
    else if(abs(newBase[2][0])>0.01)
    {
        newBase[1][2] = 1.;
        newBase[1][1] = 0.;
        newBase[1][0] = -newBase[2][2]/newBase[2][0];
        newBase[1] /= newBase[1].norm();
    }
    else
    {
        newBase[1][2] = 1.;
        newBase[1][0] = 0.;
        newBase[1][1] = -newBase[2][2]/newBase[2][1];
        newBase[1] /= newBase[1].norm();
    }
    newBase[0] = vecteur<double,3>::vectorProduct(newBase[1],newBase[2]);

    cpCoordinate.changeBase(newBase);
    dirR.changeBase(newBase);
    dirR *= distanceFromSource/dirR[2];
    if(pow(dirR[0]-cpCoordinate[0],2.)+pow(dirR[1]-cpCoordinate[1],2.)<(radius*radius))
    {
        ray2update.addLight(luminosity);
    }
}
