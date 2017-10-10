#ifndef GRAVITATIONALLENSE_H
#define GRAVITATIONALLENSE_H

#include <vector>
#include <array>

#include "Object.h"
#include "Source.h"


class GravitationalLense : public Object
{
public:

   GravitationalLense ();
   virtual ~GravitationalLense ();


   void addSource(Source* source);
   void setSourceList(std::vector<Source*> newSourceList);
   std::vector<std::vector<std::array<double,3>>> getImage();



protected:

   virtual void calculateImage() = 0;
   void sortSource();

   std::vector<Source*> sourceList;
   bool isImageUpdate;
   std::vector<std::vector<std::array<double,3>>> image;
   bool sourceSorted;
};

#endif // GRAVITATIONALLENSE_H
