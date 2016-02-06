//
//  complex.cpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/8/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#include "complex.hpp"

complex::complex(){
    re = 1; im = 0;
}

complex::complex(double x, double y) {
    re = x; im = y;
}

complex complex::operator+(const complex & other){
    return complex(re + other.getRe(), im + other.getIm());
}

complex complex::operator-(const complex & other){
    return complex(re - other.getRe(), im - other.getIm());
}

complex complex::operator*(const complex & other){
    return complex(re*other.getRe() - im*other.getIm(), re*other.getIm() + im*other.getRe());
}

complex complex::operator*(const double & other){
    return complex(re*other, im * other);
}

complex complex::operator/(const double & other) {
    return complex(re/other, im/other);
}
complex complex::operator/(const complex & other){
    return *this * (other.conjugate() / (other.modulus()*other.modulus()));
}
complex complex::operator=(const complex & other) {
    im = other.getIm();
    re = other.getRe();
    return *this;
}

double complex::squaremodulus() const {
    return re*re + im*im;
}
double complex::modulus() const{
    return sqrt(re*re + im*im);
}
double complex::arg() const {
    if (re > 0) return atan(im/re);
    if (re < 0){
        if (im < 0) return atan(im/re) - PI;
        return atan(im/re) + PI;
    }

    if (im > 0) return PI/2;
    if (im < 0) return -PI/2;
    return -1;

}
complex complex::conjugate() const{
    return complex(re, -im);
}


bool complex::operator==(const complex & other){
    return re == other.getRe() && im == other.getIm();
}

std::string complex::toString(){
    std::ostringstream ss;
    ss << '(' << re << "+i" << im << ')';
    return ss.str();
}

complex operator*(double x, complex z){
    return complex(x*z.getRe(), x*z.getIm());
}

complex operator+(double x, complex z){
    return complex(x+z.getRe(), z.getIm());
}
