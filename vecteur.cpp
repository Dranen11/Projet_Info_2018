#include "vecteur.h"

template<>
void vecteur<double,3>::setPolarCoordinate(std::array<double,3> const& coordinate)
{
    (*this)[0] = coordinate[0]*sin(coordinate[1])*cos(coordinate[2]);
    (*this)[1] = coordinate[0]*sin(coordinate[1])*sin(coordinate[2]);
    (*this)[2] = coordinate[0]*cos(coordinate[1]);
}

template<>
std::array<double,3> vecteur<double,3>::getPolarCoordinate() const
{
    std::array<double,3> result;
    result[0] = this->norm();
    result[1] = acos((*this)[2]/result[0]);
    result[2] = atan((*this)[1]/(*this)[0]);
    return result;
}

template<>
void vecteur<double,2>::setPolarCoordinate(std::array<double,2> const& coordinate)
{
    (*this)[0] = coordinate[0]*cos(coordinate[1]);
    (*this)[1] = coordinate[0]*sin(coordinate[1]);
}

template<>
std::array<double,2> vecteur<double,2>::getPolarCoordinate() const
{
    std::array<double,2> result;
    result[0] = this->norm();
    result[1] = atan((*this)[1]/(*this)[0]);
    return result;
}

template<>
void vecteur<float,3>::setPolarCoordinate(std::array<float,3> const& coordinate)
{
    (*this)[0] = coordinate[0]*sin(coordinate[1])*cos(coordinate[2]);
    (*this)[1] = coordinate[0]*sin(coordinate[1])*sin(coordinate[2]);
    (*this)[2] = coordinate[0]*cos(coordinate[1]);
}

template<>
std::array<float,3> vecteur<float,3>::getPolarCoordinate() const
{
    std::array<float,3> result;
    result[0] = this->norm();
    result[1] = acos((*this)[2]/result[0]);
    result[2] = atan((*this)[1]/(*this)[0]);
    return result;
}

template<>
void vecteur<float,2>::setPolarCoordinate(std::array<float,2> const& coordinate)
{
    (*this)[0] = coordinate[0]*cos(coordinate[1]);
    (*this)[1] = coordinate[0]*sin(coordinate[1]);
}

template<>
std::array<float,2> vecteur<float,2>::getPolarCoordinate() const
{
    std::array<float,2> result;
    result[0] = this->norm();
    result[1] = atan((*this)[1]/(*this)[0]);
    return result;
}

template<>
double vecteur<double,3>::sum() const
{
    return (*this)[0]+(*this)[1]+(*this)[2];
}

template<>
float vecteur<float,3>::sum() const
{
    return (*this)[0]+(*this)[1]+(*this)[2];
}
