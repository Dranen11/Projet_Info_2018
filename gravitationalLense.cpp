#include "gravitationalLense.h"
#include <cmath>

#include <QtCore>
#include <QObject>

#define M_G 6.67408e-11
#define M_C 299792458.


using namespace std;


gravitationalLense::gravitationalLense(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed)
    :celestialBody(mass,coordinate,speed)
{

}

void gravitationalLense::update_ray(ray &ray2update) const
{
    array<vecteur<double,3>,3> newBase, originalBase = {vecteur<double,3>({1.,0.,0.}),vecteur<double,3>({0.,1.,0.}),vecteur<double,3>({0.,0.,1.})}; //base de la lentille
    newBase[2] = coordinate-ray2update.get_posSource(); //vecteur z dans la base de la lentille correspondant à l'axe source, lentille
    double distanceFromSource =  newBase[2].norm(); //distance lentille source

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

    //adaptation des directions et position du rayon dans la nouvelle base
    vecteur<double,3> newDir = ray2update.get_direction(), newPos = ray2update.get_direction(), cpCoordinate = coordinate;
    newDir.changeBase(newBase);
    newPos.changeBase(newBase);
    cpCoordinate.changeBase(newBase);
    originalBase[0].changeBase(newBase);
    originalBase[1].changeBase(newBase);
    originalBase[2].changeBase(newBase);

    newDir *= distanceFromSource/newDir[2]; //vecteur position de l'intersection rayon plan lentille
    newPos += newDir;
    double distance2Lense = sqrt(pow(newDir[0]-cpCoordinate[0],2)+pow(newDir[1]-cpCoordinate[1],2));
    double deviationAngle = 4.*M_G*mass/(distance2Lense*M_C*M_C);
    double deviationAngleX = deviationAngle*(newDir[0]-cpCoordinate[0])/distance2Lense;
    double deviationAngleY = deviationAngle*(newDir[1]-cpCoordinate[1])/distance2Lense;
    //qDebug() << newDir[0] << " " << deviationAngleX*newDir[2];
    //qDebug() << newDir[1] << " " << deviationAngleY*newDir[2];
    newDir[0] -= deviationAngleX*newDir[2];
    newDir[1] -= deviationAngleY*newDir[2];
    newDir /= newDir.norm();
    newDir.changeBase(originalBase);
    newPos.changeBase(originalBase);

    ray2update.updateRay(newPos, newDir);
}
