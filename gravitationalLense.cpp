#include "gravitationalLense.h"
#include <cmath>

#define M_G 6.67408e-11
#define M_C 299792458.


using namespace std;


gravitationalLense::gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed)
    :celestialBody(mass,coordinate,speed)
{

}

void gravitationalLense::update_pixel(pixel& pixel2update) const
{
    update_ray(pixel2update.get_r1());
    update_ray(pixel2update.get_r2());
}


void gravitationalLense::update_ray(ray &ray2update) const
{
    array<vecteur<double,3>,3> newBase, originalBase = {vecteur<double,3>({1.,0.,0.}),vecteur<double,3>({0.,1.,0.}),vecteur<double,3>({0.,0.,1.})}; //base de la lentille
    array<array<double,3>,3> polarCoordinateBase; //dans la base de la lentille
    newBase[2] = coordinate-ray2update.get_posSource(); //vecteur z dans la base de la lentille correspondant à l'axe source, lentille
    double distanceFromSource =  newBase[2].norm(); //distance lentille source

    //creation des vecteurs de base x et y
    newBase[2] /= distanceFromSource;
    polarCoordinateBase[2] = newBase[2].getPolarCoordinate();
    polarCoordinateBase[0] = polarCoordinateBase[2];
    polarCoordinateBase[1] = polarCoordinateBase[2];
    polarCoordinateBase[0][2] += M_PI;
    polarCoordinateBase[1][1] += M_PI;
    newBase[0].setPolarCoordinate(polarCoordinateBase[0]);
    newBase[1].setPolarCoordinate(polarCoordinateBase[1]);

    //adaptation des directions et position du rayon dans la nouvelle base
    vecteur<double,3> newDir = ray2update.get_direction(), newPos = ray2update.get_direction();
    newDir.changeBase(newBase);
    newPos.changeBase(newBase);
    originalBase[0].changeBase(newBase);
    originalBase[1].changeBase(newBase);
    originalBase[2].changeBase(newBase);

    newDir *= distanceFromSource/newDir[2]; //vecteur position de l'intersection rayon plan lentille
    newPos += newDir;
    double distance2Lense = sqrt(newDir[0]*newDir[0]+newDir[1]*newDir[1]);
    double deviationAngle = 4.*M_G*mass/(distance2Lense*M_C*M_C);
    double deviationAngleX = deviationAngle*newDir[0]/distance2Lense;
    double deviationAngleY = deviationAngle*newDir[1]/distance2Lense;
    newDir[0] -= deviationAngleX*newDir[2];
    newDir[1] -= deviationAngleY*newDir[2];
    newDir /= newDir.norm();
    newDir.changeBase(originalBase);
    newPos.changeBase(originalBase);

    ray2update.updateRay(newPos, newDir);
}
