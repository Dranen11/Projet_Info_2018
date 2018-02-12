#ifndef PIXEL_H
#define PIXEL_H

#include <vector>
#include "celestialBody.h"
#include "vecteur.h"
#include "ray.h"

class celestialBody;

class pixel
{
public:
    pixel();
    pixel(ray const& r1, ray const& r2);
    void set_initR1(ray const& newRay);
    void set_initR2(ray const& newRay);
    ray get_initR1() const;
    ray get_initR2() const;
    ray const& get_r1() const;
    ray const& get_r2() const;
    ray& get_r1();
    ray& get_r2();
    vecteur<double,3> get_light() const;
    bool getBlocked() const;

    void addLight(vecteur<double,3> newLight);
    void Blocked();

    void calculatePixel(std::vector<celestialBody const *> objectList, std::size_t maxIter = 100);

protected:
    void sortObjectList(std::vector<celestialBody const *>& objectList, celestialBody const * last);

    vecteur<double,3> light;
    bool blocked;
    ray r1,r2,initR1,initR2;
};

#endif // PIXEL_H
