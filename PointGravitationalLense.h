#ifndef POINTGRAVITATIONALLENSE_H
#define POINTGRAVITATIONALLENSE_H

#include "GravitationalLense.h"

class PointGravitationalLense : public GravitationalLense
{
public:

   PointGravitationalLense ();
   virtual ~PointGravitationalLense ();

protected:
   virtual void calculateImage();

};

#endif // POINTGRAVITATIONALLENSE_H
