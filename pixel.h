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
    pixel(ray r1, ray r2);
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
    void sortObjectList(std::vector<celestialBody const *>& objectList);

    vecteur<double,3> light;
    bool blocked;
    ray r1,r2;
};

#endif // PIXEL_H
