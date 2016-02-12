//
//  complex.hpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/8/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#ifndef complex_hpp
#define complex_hpp

#include <stdio.h>
#include <string>
#include <math.h>
#include <sstream>

#define PI 3.141592653589793


class complex{
public:
    /* Constructors */
    complex();
    complex(double x, double y);

    /* Operators */
    complex operator+(const complex & other);
    complex operator-(const complex & other);
    complex operator*(const complex & other);
    complex operator*(const double & other);
    complex operator/(const double  & other);
    complex operator/(const complex & other);

    complex operator=(const complex & other);
    bool operator==(const complex & other);
    /* Functions */
    // Operations
    complex conjugate() const;
    double squaremodulus() const;
    double modulus() const;
    double arg() const;
    //getters/setters
    double getRe() const { return re; }
    double getIm() const { return im; }
    void setRe(double r) { re = r; }
    void setIm(double i) { im = i; }

    std::string toString();


private:
    double re;
    double im;

};

class complexExp{
public:

private:
    double r;
    double theta;
};

complex operator*(double x, complex z);
complex operator+(double x, complex z);

static const complex unitRe(1,0);
static const complex unitIm(0,1);

typedef complex cmplx;

#endif /* complex_hpp */
