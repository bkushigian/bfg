#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <math.h>
#include <complex>
#include <iostream>
#include <sstream>
#include <vector>
#include "../Globals/globals.hpp"

class poly {
private:
	std::vector<cmplx> coef;			// Coefficients in complex numbers
	int deg;
	int ord;
	char var;
public:
	poly(std::string s, char v;);
	std::vector<cmplx> parseString(std::string s, char v);
}

#endif
