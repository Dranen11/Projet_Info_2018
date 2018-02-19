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
    if(result[0] > 0)
    {
        result[1] = acos((*this)[2]/result[0]);
        if(abs((*this)[0])>1e-15)
        {
            result[2] = atan((*this)[1]/(*this)[0]);
        }
        else if((*this)[0]>0.)
        {
            result[2] = M_PI/2.;
        }
        else
        {
            result[2] = -M_PI/2.;
        }
    }
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
    if(result[0] > 0)
    {
        result[1] = acos((*this)[2]/result[0]);
        if(abs((*this)[0])>1e-15)
        {
            result[2] = atan((*this)[1]/(*this)[0]);
        }
        else if((*this)[0]<0.)
        {
            result[2] = -M_PI/2.;
        }
        else
        {
            result[2] = M_PI/2.;
        }
    }
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

template<>
vecteur<double,3> vecteur<double,3>::vectorProduct(vecteur<double,3> const& A, vecteur<double,3> const& B)
{
    return vecteur<double,3>({A[1]*B[2]-A[2]*B[1], A[2]*B[0]-A[0]*B[2], A[0]*B[1]-A[1]*B[0]});
}

template<>
vecteur<float,3> vecteur<float,3>::vectorProduct(vecteur<float,3> const& A, vecteur<float,3> const& B)
{
    return vecteur<float,3>({A[1]*B[2]-A[2]*B[1], A[2]*B[0]-A[0]*B[2], A[0]*B[1]-A[1]*B[0]});
}

template<>
double vecteur<double,3>::scalarProduct(vecteur<double,3> const& A, vecteur<double,3> const& B)
{
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
}

template<>
double vecteur<double,3>::norm2() const
{
    return ((*this)[0]*(*this)[0])+((*this)[1]*(*this)[1])+((*this)[2]*(*this)[2]);
}

template<>
float vecteur<float,3>::scalarProduct(vecteur<float,3> const& A, vecteur<float,3> const& B)
{
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
}

template<>
float vecteur<float,3>::norm2() const
{
    return ((*this)[0]*(*this)[0])+((*this)[1]*(*this)[1])+((*this)[2]*(*this)[2]);
}
