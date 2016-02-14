//
//  mandelbrot.hpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/8/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#ifndef mandelbrot_hpp
#define mandelbrot_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include "../Globals/globals.hpp"
#include "../math/complex.hpp"
#include "fractal.hpp"
#include "../Display/winManager.hpp"

class winManager;
class mandelbrot: public fractal {
public:
    mandelbrot();
    mandelbrot(complex tl, complex br, Uint16 height, Uint16 width, Uint16 max);
    ~mandelbrot();
	/* Inherited Functions */

    void populateGrid();
	sf::Uint16* getGrid();
	std::string getName() { return name; }
	FRACTAL_TYPE getType() { return type; }
	DSP_MODE getDisplayMode() { return displayMode; }
	void setName(std::string n) { name = n; }
	sf::Uint16 iterations(complex z);
    void resizeGrid(Uint16 h, Uint16 w);
	Uint16 getGridAt(Uint16 y, Uint16 x);
	Uint16 getHeight() { return height; }
	Uint16 getWidth() { return width; }
	void draw();
    std::string toString();
    std::string toString(Uint16 chrs);


private:
	std::string chars; 
	int charSize;
    complex topleft;
    complex bottomright;
	Uint16 maxiter;
    Uint16* grid;
    Uint16 width;
    Uint16 height;
	DSP_MODE displayMode;
};

#endif /* mandelbrot_hpp */
