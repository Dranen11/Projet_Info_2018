#ifndef SOURCE_H
#define SOURCE_H

#include "Object.h"

class Source : public Object
{
public:

   Source ();
   virtual ~Source ();

   virtual std::array<double,3> getPixel(std::array<double,3> position, std::array<double,3> size) const = 0;
   double getLuminosity() const;
   void setLuminosity(double newLuminosity);
   bool isUpdate() const;

protected:

   double luminosity;
   bool sourceUpdate;

};

#endif // SOURCE_H
