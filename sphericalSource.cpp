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
    vecteur<double,3> meanPos = 0.5*(pixel2update.get_r1().get_posSource()+pixel2update.get_r2().get_posSource());
    vecteur<double,3> dirSource = coordinate-meanPos;

    vecteur<double,3> dir1 = pixel2update.get_r1().get_posSource()+pixel2update.get_r1().get_direction()-meanPos;
    vecteur<double,3> dir2 = pixel2update.get_r2().get_posSource()+pixel2update.get_r2().get_direction()-meanPos;
    dir1 *= (dirSource.norm()/dir1.norm());
    dir2 *= (dirSource.norm()/dir2.norm());

    array<double,3> aDir1 = dir1.getPolarCoordinate(), aDir2 = dir2.getPolarCoordinate(), aDirSource = dirSource.getPolarCoordinate();
    double angleRadius = atan(radius/aDirSource[0]);

    bool testCorner1 = (aDirSource[1]-angleRadius) > aDir1[1] && (aDirSource[1]-angleRadius) < aDir2[1] && (aDirSource[2]-angleRadius) > aDir1[2] && (aDirSource[2]-angleRadius) > aDir2[2];
    bool testCorner2 = (aDirSource[1]-angleRadius) > aDir1[1] && (aDirSource[1]-angleRadius) < aDir2[1] && (aDirSource[2]+angleRadius) > aDir1[2] && (aDirSource[2]+angleRadius) > aDir2[2];
    bool testCorner3 = (aDirSource[1]+angleRadius) > aDir1[1] && (aDirSource[1]+angleRadius) < aDir2[1] && (aDirSource[2]-angleRadius) > aDir1[2] && (aDirSource[2]-angleRadius) > aDir2[2];
    bool testCorner4 = (aDirSource[1]+angleRadius) > aDir1[1] && (aDirSource[1]+angleRadius) < aDir2[1] && (aDirSource[2]+angleRadius) > aDir1[2] && (aDirSource[2]+angleRadius) > aDir2[2];
    bool testSegment1 = (aDirSource[1]+angleRadius) > aDir1[1] && (aDirSource[1]+angleRadius) < aDir2[1] && (aDirSource[2]-angleRadius) < aDir1[2] && (aDirSource[2]+angleRadius) > aDir2[2];
    bool testSegment2 = (aDirSource[1]-angleRadius) > aDir1[1] && (aDirSource[1]-angleRadius) < aDir2[1] && (aDirSource[2]-angleRadius) < aDir1[2] && (aDirSource[2]+angleRadius) > aDir2[2];
    bool testSegment3 = (aDirSource[2]+angleRadius) > aDir1[2] && (aDirSource[2]+angleRadius) < aDir2[2] && (aDirSource[1]-angleRadius) < aDir1[1] && (aDirSource[1]+angleRadius) > aDir2[1];
    bool testSegment4 = (aDirSource[2]-angleRadius) > aDir1[2] && (aDirSource[2]-angleRadius) < aDir2[2] && (aDirSource[1]-angleRadius) < aDir1[1] && (aDirSource[1]+angleRadius) > aDir2[1];
    bool testEnglobed = (aDirSource[1]-angleRadius) < aDir1[1] && (aDirSource[1]+angleRadius) > aDir2[1] && (aDirSource[2]-angleRadius) < aDir1[2] && (aDirSource[2]+angleRadius) > aDir2[2];

    if(testCorner1 || testCorner2 || testCorner3 || testCorner4 || testSegment1 || testSegment2 || testSegment3 || testSegment4 || testEnglobed)
    {
        pixel2update.addLight(luminosity);
    }
}
