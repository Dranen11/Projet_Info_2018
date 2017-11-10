#include <cmath>
#include <iostream>
#include <ctime>
#include <chrono>
#include <array>
#include <algorithm>
#include <random>
#include "test.h"

using namespace std;

void test_vecteur(std::size_t nPASS)
{
    test_vecteurOperator(nPASS);
    test_vecteurElementWise(nPASS);
    test_vecteurLinearAlgebra(nPASS);
    test_vecteurPolarCoordinate(nPASS);
}

void test_vecteurPolarCoordinate(std::size_t nPASS)
{
    bool valid = true;
    double error = 0.;
    random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(10, 1000);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    cout<<"Test 1 N=2"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 2;
        vecteur<double, N> A,C;
        array<double, N> B;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
        }
        B = A.getPolarCoordinate();
        C.setPolarCoordinate(B);
        if(abs(B[0]-A.norm())>1e-10)
        {
            valid = false;
            error = max(error,abs(B[0]-A.norm()));
        }
        if(abs(B[1]-2*atan(A[1]/(A[0]+A.norm())))>1e-10)
        {
            valid = false;
            error = max(error,abs(B[1]-2*atan(A[1]/(A[0]+A.norm()))));
        }
        for(size_t j =0; j< N; j++)
        {
            if(abs(A[j]-C[j])>1e-10)
            {
                valid = false;
                error = max(error,abs(A[j]-C[j]));
            }
        }

    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }


    cout<<"Test 2 N=3"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 3;
        vecteur<double, N> A,C;
        array<double, N> B;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
        }
        B = A.getPolarCoordinate();
        C.setPolarCoordinate(B);

        if(abs(B[0]-A.norm())>1e-10)
        {
            valid = false;
            error = max(error,abs(B[0]-A.norm()));
        }
        if(abs(B[1]-acos(A[2]/A.norm()))>1e-10)
        {
            valid = false;
            error = max(error,abs(B[1]-acos(A[2]/A.norm())));
        }
        if(abs(B[2]-atan(A[1]/A[0]))>1e-10)
        {
            valid = false;
            error = max(error,abs(B[2]-atan(A[1]/A[0])));
        }

        for(size_t j =0; j< N; j++)
        {
            if(abs(A[j]-C[j])>1e-10)
            {
                valid = false;
                error = max(error,abs(A[j]-C[j]));
            }
        }

    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }
    cout << endl;
}

void test_vecteurOperator(std::size_t nPASS)
{
    bool valid = true;
    double error = 0.;
    random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(10, 1000);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    cout<<"Test Vecteur Operator"<<endl<<"Test 1 Operator +"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A,B,C;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
            B[j] = dis(gen);
        }
        C = A+B;

        for(size_t j =0; j< N; j++)
        {
            if(abs(C[j]-(A[j]+B[j]))>1e-10)
            {
                valid = false;
                error = max(error,abs(C[j]-(A[j]+B[j])));
            }
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }

    cout<<"Test 2 Operator -"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A,B,C;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
            B[j] = dis(gen);
        }
        C = A-B;

        for(size_t j =0; j< N; j++)
        {
            if(abs(C[j]-(A[j]-B[j]))>1e-10)
            {
                valid = false;
                error = max(error,abs(C[j]-(A[j]-B[j])));
            }
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }

    cout<<"Test 3 Operator *"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A,B,C;
        double b,c;
        b = dis(gen);
        c = dis(gen);
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
        }
        B = b*A;
        C = A*c;

        for(size_t j =0; j< N; j++)
        {
            if(abs(C[j]-(A[j]*c))>1e-10)
            {
                valid = false;
                error = max(error,abs(C[j]-(A[j]*c)));
            }
            if(abs(B[j]-(b*A[j]))>1e-10)
            {
                valid = false;
                error = max(error,abs(B[j]-(b*A[j])));
            }
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }
    cout << endl;
}

void test_vecteurElementWise(std::size_t nPASS)
{
    bool valid = true;
    double error = 0.;
    random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(10, 1000);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    cout<<"Test Vecteur ElementWise"<<endl<<"Test 1 Multiply"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A,B,C;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
            B[j] = dis(gen);
        }
        C = vecteur<double,N>::multiplyElementWise(A,B);

        for(size_t j =0; j< N; j++)
        {
            if(abs(C[j]-(A[j]*B[j]))>1e-10)
            {
                valid = false;
                error = max(error,abs(C[j]-(A[j]*B[j])));
            }
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }

    cout << endl;
}

void test_vecteurLinearAlgebra(std::size_t nPASS)
{
    bool valid = true;
    double error = 0.;
    random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(10, 1000);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    cout<<"Test Vecteur LinearAlgebra"<<endl<<"Test 1 Norm2"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A;
        double value=0;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
        }

        for(size_t j =0; j< N; j++)
        {
            value += A[j]*A[j];
        }
        if(abs(A.norm2()-value)>1e-10)
        {
            valid = false;
            error = max(error,abs(A.norm2()-value));
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }

    cout<<"Test 2 Norm"<<endl;
    for(size_t i = 0; i < nPASS; i++)
    {
        constexpr size_t N = 1000;
        vecteur<double, N> A;
        double value=0;
        for(size_t j =0; j< N; j++)
        {
            A[j] = dis(gen);
        }

        for(size_t j =0; j< N; j++)
        {
            value += A[j]*A[j];
        }
        value = sqrt(value);
        if(abs(A.norm()-value)>1e-10)
        {
            valid = false;
            error = max(error,abs(A.norm()-value));
        }
    }
    if(valid)
    {
        cout << "Test Passed"<<endl;
    }
    else
    {
        cout << "Test Failed, max error :"<<error<<endl;
        valid = true;
        error = 0.;
    }
    cout << endl;
}
