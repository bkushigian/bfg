//
//  julia.hpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/9/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#ifndef julia_hpp
#define julia_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include "../math/complex.hpp"
#include "fractal.hpp"
#include "../Globals/globals.hpp"
using namespace sf;

typedef complex cmplx;

class julia : public fractal {
public:
    julia();
    julia(complex tl, complex br, Uint16 height, Uint16 width, Uint16 max);
    ~julia();
	/* Inherited functions */
    void populateGrid();
    void resizeGrid(Uint16 h, Uint16 w);
    Uint16* getGrid();
	std::string getName() { return name; }
	FRACTAL_TYPE getType() { return type; }
	void setName(std::string n) { name = n; }

	/*  */
	Uint16 iterations(complex z);
    Uint16 getGridAt(Uint16 y, Uint16 x);
    Uint16 getHeight() { return height; }
    Uint16 getWidth() { return width; }
    void setC(complex C) { this->C = C;}
    complex getC() { return C; }
    std::string toString();
    std::string toString(Uint16 chrs);
private:
    int charSize;
	std::string chars;
    complex topleft;
    complex bottomright;
    complex C;
    Uint16 maxiter;
    Uint16* grid;
    Uint16 width;
    Uint16 height;
		
	std::string name;
};
#endif /* julia_hpp */
