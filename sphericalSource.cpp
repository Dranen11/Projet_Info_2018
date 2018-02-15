#include "sphericalSource.h"
#include <array>
#include <cmath>

using namespace std;

sphericalSource::sphericalSource(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, vecteur<double,3> luminosity, double radius)
    :celestialBody(mass, coordinate, speed), luminosity(luminosity), radius(radius), surface(4.*M_PI*pow(radius,3)/3.)
{

}

void sphericalSource::update_pixel(pixel &pixel2update) const
{
    vecteur<double,3> meanPos = 0.5*(pixel2update.get_r1().get_posSource()+pixel2update.get_r2().get_posSource()), cpCoordinate = coordinate;
    vecteur<double,3> dirSource = coordinate-meanPos, dirR1 = pixel2update.get_r1().get_direction(), dirR2 = pixel2update.get_r2().get_direction();

    array<vecteur<double,3>,3> newBase; //base de la lentille
    newBase[2] = dirSource; //vecteur z dans la base de la lentille correspondant à l'axe source, lentille
    double distanceFromSource =  newBase[2].norm(); //distance lentille source
    newBase[2] /= distanceFromSource;

    if(abs(newBase[2][2])>0.01)
    {
        newBase[1][1] = 1.;
        newBase[1][0] = 0.;
        newBase[1][2] = newBase[2][1]/newBase[2][2];
        newBase[1] /= newBase[1].norm();
    }
    else if(abs(newBase[2][0])>0.01)
    {
        newBase[1][2] = 1.;
        newBase[1][1] = 0.;
        newBase[1][0] = newBase[2][2]/newBase[2][0];
        newBase[1] /= newBase[1].norm();
    }
    else
    {
        newBase[1][2] = 1.;
        newBase[1][0] = 0.;
        newBase[1][1] = newBase[2][2]/newBase[2][1];
        newBase[1] /= newBase[1].norm();
    }
    newBase[0] = vecteur<double,3>::vectorProduct(newBase[1],newBase[2]);

    cpCoordinate.changeBase(newBase);
    dirR1.changeBase(newBase);
    dirR2.changeBase(newBase);
    dirR1 *= distanceFromSource/dirR1[2];
    dirR2 *= distanceFromSource/dirR2[2];
    vecteur<double, 2> origin({min(dirR1[0],dirR2[0]),min(dirR1[1],dirR2[1])}), diagonal({abs(dirR1[0]-dirR2[0]),abs(dirR1[1]-dirR2[1])});

    double x_overlap = max(0., min(origin[0]+diagonal[0], cpCoordinate[0]+radius) - max(origin[0], cpCoordinate[0]-radius));
    double y_overlap = max(0., min(origin[1]+diagonal[1], cpCoordinate[1]+radius) - max(origin[1], cpCoordinate[1]-radius));
    double overlapArea = x_overlap * y_overlap;
    if(overlapArea > 0.)
    {
        pixel2update.addLight(luminosity);
    }
}
