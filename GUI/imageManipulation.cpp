#include "imageManipulation.h"
#include <stdlib.h>
#include <stdint.h>
#include <cmath>

using namespace std;


unsigned char* convertImageRGB32(std::vector<std::vector<vecteur<double,3>>> const& image, double min, double max, size_t alignement)
{
    //creation of the memory space for storage the RGB32 image
    size_t n_row = image.size(), n_column = image[0].size();
    unsigned char* final_image = (unsigned char*) aligned_alloc( alignement, 4*n_row*n_column);
    vector<vector<double>> luminosity(calculateLuminosity(image));

    //calculation of the min and maximum luminosity of the image if not defined (corresponding to black and white of the image)
    if(max < 0. || min < 0.)
    {
        double cmin, cmax;
        imageMinMax(luminosity,cmin,cmax);
        if(max < 0.) {max = cmax;}
        if(min < 0.) {min = cmin;}
    }

    for(size_t i = 0; i < image.size(); i++)
    {
        for(size_t j =  0; j < image.size(); j++)
        {
            vecteur<double, 3> color = calculateColor(image[i][j], luminosity[i][j]);
            for(size_t k = 0; k < 3; k++)
            {
               final_image[i*n_column+j*4+k] = static_cast<unsigned char>(255.*color[k]*((luminosity[i][j]-min)/(max-min)));
            }
        }
    }


    return final_image;
}



void imageMinMax(const vector<vector<double>> & luminosity, double &min, double &max)
{
    //initialisation
    min = HUGE_VAL;
    max = 0.;

    for(size_t i = 0; i < luminosity.size(); i++)
    {
        for(size_t j =  0; j < luminosity.size(); j++)
        {
            if(luminosity[i][j]>max) {max = luminosity[i][j];}
            else if(luminosity[i][j]<min) {min = luminosity[i][j];}
        }
    }
}


vector<vector<double>> calculateLuminosity(vector<vector<vecteur<double,3>>> const& image)
{
    vector<vector<double>> luminosity(image.size(),vector<double>(image[0].size()));
    for(size_t i = 0; i < image.size(); i++)
    {
        for(size_t j =  0; j < image.size(); j++)
        {
            luminosity[i][j] = image[i][j].sum();
        }
    }
    return luminosity;
}

vecteur<double, 3> calculateColor(vecteur<double,3> const& cluminosity, double const& totalLuminosity)
{
    vecteur<double,3> result = cluminosity/totalLuminosity;
    result /= result.max();
    return result;
}
