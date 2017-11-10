#include "celestialBody.h"

celestialBody::celestialBody(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed)
:mass(mass),coordinate(coordinate),speed(speed)
{

}

celestialBody::~celestialBody()
{

}

void celestialBody::timeStep(double dt)
{
    coordinate[0] += speed[0]*dt;
    coordinate[1] += speed[1]*dt;
    coordinate[2] += speed[2]*dt;
}


