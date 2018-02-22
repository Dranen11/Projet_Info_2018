#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H

#include <vector>
#include "../vecteur.h"

unsigned char* convertImageRGB32(std::vector<std::vector<vecteur<double,3>>> const& image, double min = 0., double max = -1., std::size_t alignement = 4);
std::vector<std::vector<double>> calculateLuminosity(std::vector<std::vector<vecteur<double,3>>> const& image);
void imageMinMax(std::vector<std::vector<double>> const& luminosity, double& min, double& max);
vecteur<double, 3> calculateColor(vecteur<double,3> const& luminosity);


#endif // IMAGEMANIPULATION_H

