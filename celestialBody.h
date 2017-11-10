#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "vecteur.h"
#include "pixel.h"

class pixel;

class celestialBody
{
public:

   celestialBody(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed);
   virtual ~celestialBody();

   virtual void timeStep(double dt);
   virtual void update_pixel(pixel& pixel2update) const = 0;

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
