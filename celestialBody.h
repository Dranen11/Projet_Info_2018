#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "vecteur.h"
#include "ray.h"

//some physics constant
#define C_G 6.67408e-11
#define C_C 299792458.
#define C_H 6.62606957e-34
#define C_Kb 1.3806488e-23

class ray;

//abstract class in order to define an celestial object which could interact with a ray of light
class celestialBody
{
public:

   celestialBody(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed);
   virtual ~celestialBody();

   virtual void timeStep(double dt);
   virtual void update_ray(ray& ray2update, celestialBody* next) const = 0;

   vecteur<double,3> getCoordinate() const
   {
      return coordinate;
   }

   double getMass() const
   {
      return mass;
   }

   vecteur<double,3> getSpeed() const
   {
      return speed;
   }

   bool get_hasChange() const
   {
       return hasChange;
   }


protected:

   bool hasChange;
   double mass;
   vecteur<double,3> coordinate;
   vecteur<double,3> speed;


};

#endif // CELESTIALBODY_H
