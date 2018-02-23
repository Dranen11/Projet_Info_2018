#include "star.h"
#include <cmath>

#include <QtCore>
#include <QObject>

using namespace std;

#define N_INTEGRATION_INTERVAL 100

star::star(double mass, vecteur<double,3> coordinate, vecteur<double,3> speed, double temperature, double radius)
    : celestialBody(mass, coordinate, speed), sphericalSource(mass, coordinate, speed, blackBodyLuminosity(temperature, radius), radius), gravitationalLense(mass, coordinate, speed)
{

}

//a star is a spherical source and a gravitational lense
void star::update_ray(ray& ray2update, celestialBody* next) const
{
    sphericalSource::update_ray(ray2update,NULL);
    gravitationalLense::update_ray(ray2update,next);
}

inline double plankLawNormalized(double lambda, double temperature, double meanLambda, double stdLambda)
{
    //plank law normalized by a gaussian for the detection width
    return (2.*M_PI*C_H*C_C*C_C/((pow(lambda,5.))*(exp(C_H*C_C/(C_Kb*lambda*temperature))-1.)))*exp(-pow(lambda-meanLambda,2.)/(2.*stdLambda*stdLambda));
}

//calculate the RGB luminosity of a black body
vecteur<double,3> star::blackBodyLuminosity(double temperature, double radius)
{
    array<array<double,2>,3> lambdaLimits({array<double,2>({533e-9,30e-9}),array<double,2>({437e-9,30e-9}),array<double,2>({584e-9,30e-9})}); //in nanometer
    double surface = 4.*M_PI*radius*radius;
    vecteur<double, 3> result({0.,0.,0.});

    for(size_t i = 0; i < 3; i++)
    {
        //Integration by Simpson algorithm
        double lambdaUp = lambdaLimits[i][0]+2.*lambdaLimits[i][1]; //maxLambda
        double lambdaDown = lambdaLimits[i][0]-2.*lambdaLimits[i][1]; //minLambda
        double intervalLength = (lambdaUp-lambdaDown)/N_INTEGRATION_INTERVAL;
        for(size_t j = 0; j < N_INTEGRATION_INTERVAL; j++)
        {
            double lmin = lambdaDown+intervalLength*static_cast<double>(j);
            double lmax = lambdaDown+intervalLength*static_cast<double>(j+1);
            double lmean = 0.5*(lmin+lmax);
            result[i] += intervalLength*plankLawNormalized(lmin, temperature, lambdaLimits[i][0], lambdaLimits[i][1]);
            result[i] += 4.*intervalLength*plankLawNormalized(lmean, temperature, lambdaLimits[i][0], lambdaLimits[i][1]);
            result[i] += intervalLength*plankLawNormalized(lmax, temperature, lambdaLimits[i][0], lambdaLimits[i][1]);
            result[i] /= 6;
        }
    }
    result *= surface;
    vecteur<double,3> test = 255.*result/result.max();
    qDebug() << test[0] << " " << test[1] << " " << test[2];
    return result;
}

