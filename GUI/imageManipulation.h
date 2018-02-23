#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H

#include <vector>
#include "../vecteur.h"

//convert the table of luminosity in RGB32 32bit aligned image
unsigned char* convertImageRGB32(std::vector<std::vector<vecteur<double,3>>> const& image, double min = 0., double max = -1., std::size_t alignement = 4);
//calculate the total luminosity of a pixel
std::vector<std::vector<double>> calculateLuminosity(std::vector<std::vector<vecteur<double,3>>> const& image);
//calculate the maximum and the minimum luminosity of the image
void imageMinMax(std::vector<std::vector<double>> const& luminosity, double& min, double& max);
//calculate a vector with the color information between 0 and 1 for a given luminosity vector
vecteur<double, 3> calculateColor(vecteur<double,3> const& luminosity);


#endif // IMAGEMANIPULATION_H

