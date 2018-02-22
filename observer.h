#ifndef OBSERVER_H
#define OBSERVER_H

#include <array>
#include <vector>
#include "gravitationalLense.h"
#include "vecteur.h"

class Observer
{
public:
    Observer(vecteur<double, 3> pointingVector, double fov, std::array<uint32_t,2> resolution);

    void set_objectList(std::vector<celestialBody *> const& newObjectList);
    std::vector<celestialBody *> get_objectList() const;
    void set_pointingVector(vecteur<double, 3> const& newVector);
    vecteur<double, 3> get_pointingVector() const;
    std::array<uint32_t,2> get_resolution() const;
    void set_resolution(std::array<uint32_t,2> const& newResolution);
    double get_fov() const;
    void set_fov(double newFOV);
    size_t get_maxIterImage() const;
    void set_maxIterImage(size_t maxIter);
    std::vector<std::vector<vecteur<double,3>>> getImage();

protected:
    void calculateImage();
    void sortObjectList();
    void newResolution();
    void changeView();
    void testUpdate();

    double fov;
    size_t maxIterImage;
    bool isUpdate;
    std::vector<celestialBody *> objectList;
    std::array<uint32_t,2> resolution;
    vecteur<double, 3> pointingVector;
    std::vector<std::vector<vecteur<double,3>>> image;
};

#endif // OBSERVER_H
