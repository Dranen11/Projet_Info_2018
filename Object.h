#ifndef OBJECT_H
#define OBJECT_H

#include <array>

class Object
{
public:

   Object(double mass, std::array<double,3> coordinate, std::array<double,3> speed);
   Object(){};
   virtual ~Object();

   void setCoordinate (std::array<double,3> new_var)    {
         coordinate = new_var;
   }

   std::array<double,3> getCoordinate ()    {
      return coordinate;
   }

   void setMass (double new_var)    {
         mass = new_var;
   }

   double getMass ()    {
      return mass;
   }

   void setSpeed (std::array<double,3> new_var)    {
         speed = new_var;
   }

   std::array<double,3> getSpeed ()    {
      return speed;
   }


protected:

   double mass;
   std::array<double,3> coordinate;
   std::array<double,3> speed;


};

#endif // OBJECT_H
