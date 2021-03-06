#ifndef VECTEUR
#define VECTEUR

#include <cmath>
#include <array>

//define a vector
template<typename T, std::size_t N>
class vecteur : public std::array<T,N>
{
public:
    vecteur();
    vecteur(std::array<T,N> input);

    T norm() const;
    T norm2() const;
    vecteur<T,N>& operator*=(T const& value);
    vecteur<T,N>& operator/=(T const& value);
    vecteur<T,N>& operator+=(vecteur<T,N>const& B);
    vecteur<T,N>& operator-=(vecteur<T,N>const& B);

    static vecteur<T,N> multiplyElementWise(vecteur<T,N> const& A, vecteur<T,N> const& B);
    static T scalarProduct(vecteur<T,N> const& A, vecteur<T,N> const& B);
    static vecteur<T,N> vectorProduct(vecteur<T,N> const& A, vecteur<T,N> const& B);
    static vecteur<T,N> createFromPolarCoordinate(std::array<T,N> const& coordinate);
    static vecteur<T,N> createFromAngularCoordinate(std::array<T,N> const& coordinate);

    void changeBase(std::array<vecteur<T,N>,N> base);
    void setPolarCoordinate(std::array<T,N> const& coordinate);
    void setAngularCoordinate(std::array<T,N> const& coordinate);
    std::array<T,N> getPolarCoordinate() const;
    std::array<T,N> getAngularCoordinate() const;

    T sum() const;
    T max() const;
};

template<typename T, std::size_t N>
vecteur<T,N> operator+(vecteur<T,N> const& A, vecteur<T,N> const& B);
template<typename T, std::size_t N>
vecteur<T,N> operator-(vecteur<T,N> const& A, vecteur<T,N> const& B);
template<typename T, std::size_t N>
vecteur<T,N> operator*(T const& value, vecteur<T,N> const& inputVecteur);
template<typename T, std::size_t N>
vecteur<T,N> operator*(vecteur<T,N> const& inputVecteur, T const& value);
template<typename T, std::size_t N>
vecteur<T,N> operator/(vecteur<T,N> const& inputVecteur, T const& value);


template<typename T, std::size_t N>
vecteur<T,N>::vecteur()
{

}

template<typename T, std::size_t N>
vecteur<T,N>::vecteur(std::array<T,N> input)
:std::array<T,N>(input)
{

}

template<typename T, std::size_t N>
vecteur<T,N> vecteur<T,N>::createFromPolarCoordinate(std::array<T,N> const& coordinate)
{
    vecteur<T,N> result;
    result.setPolarCoordinate(coordinate);
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N> vecteur<T,N>::createFromAngularCoordinate(std::array<T,N> const& coordinate)
{
    vecteur<T,N> result;
    result.setAngularCoordinate(coordinate);
    return result;
}

template<typename T, std::size_t N>
void vecteur<T,N>::changeBase(std::array<vecteur<T,N>,N> base)
{
    vecteur<T,N> ante(*this);
    for(std::size_t i = 0; i < N; i++)
    {
        (*this)[i] = vecteur<T,N>::scalarProduct(ante,base[i]);
    }
}

template<typename T, std::size_t N>
T vecteur<T,N>::norm() const
{
    return sqrt(norm2());
}


template<typename T, std::size_t N>
T vecteur<T,N>::norm2() const
{
    T result = (*this)[0]*(*this)[0];
    for(std::size_t i = 1; i < N; i++)
    {
        result += (*this)[i]*(*this)[i];
    }
    return result;
}


template<typename T, std::size_t N>
vecteur<T,N>& vecteur<T,N>::operator*=(T const& value)
{
    for(std::size_t i = 0; i < N; i++)
    {
        (*this)[i] *= value;
    }
    return (*this);
}

template<typename T, std::size_t N>
vecteur<T,N> operator*(vecteur<T,N> const& inputVecteur, T const& value)
{
    vecteur<T,N> result = inputVecteur;
    result *= value;
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N> operator*(T const& value, vecteur<T,N> const& inputVecteur)
{
    vecteur<T,N> result = inputVecteur;
    result *= value;
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N>& vecteur<T,N>::operator/=(T const& value)
{
    for(std::size_t i = 0; i < N; i++)
    {
        (*this)[i] /= value;
    }
    return (*this);
}

template<typename T, std::size_t N>
vecteur<T,N> operator/(vecteur<T,N> const& inputVecteur, T const& value)
{
    vecteur<T,N> result = inputVecteur;
    result /= value;
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N>& vecteur<T,N>::operator+=(vecteur<T,N>const& B)
{
    for(std::size_t i = 0; i < N; i++)
    {
        (*this)[i] += B[i];
    }
    return (*this);
}

template<typename T, std::size_t N>
vecteur<T,N> operator+(vecteur<T,N> const& A, vecteur<T,N> const& B)
{
    vecteur<T,N> result = A;
    result += B;
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N>& vecteur<T,N>::operator-=(vecteur<T,N>const& B)
{
    for(std::size_t i = 0; i < N; i++)
    {
        (*this)[i] -= B[i];
    }
    return (*this);
}

template<typename T, std::size_t N>
vecteur<T,N> operator-(vecteur<T,N> const& A, vecteur<T,N> const& B)
{
    vecteur<T,N> result = A;
    result -= B;
    return result;
}

template<typename T, std::size_t N>
vecteur<T,N> vecteur<T,N>::multiplyElementWise(vecteur<T,N> const& A, vecteur<T,N> const& B)
{
    vecteur<T,N> result;
    for(size_t i = 0; i < N; i++)
    {
        result[i] = A[i]*B[i];
    }
    return result;
}

template<typename T, std::size_t N>
T vecteur<T,N>::scalarProduct(vecteur<T,N> const& A, vecteur<T,N> const& B)
{
    T result = A[0]*B[0];
    for(size_t i = 1; i < N; i++)
    {
        result += A[i]*B[i];
    }
    return result;
}

template<typename T, std::size_t N>
T vecteur<T,N>::sum() const
{
    T result = 0;
    for(size_t i = 0; i < N; i++)
    {
        result += (*this)[i];
    }
    return result;
}

template<typename T, std::size_t N>
T vecteur<T,N>::max() const
{
    T result = (*this)[0];
    for(size_t i = 1; i < N; i++)
    {
        if(result < (*this)[i])
            result = (*this)[i];
    }
    return result;
}

#endif // VECTEUR

