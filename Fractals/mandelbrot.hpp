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
#include "../math/complex.hpp"
#include "fractal.hpp"

using namespace sf;

typedef complex cmplx;

class mandelbrot: public fractal {
public:
    mandelbrot();
    mandelbrot(complex tl, complex br, Uint16 height, Uint16 width, Uint16 max);
    ~mandelbrot();
    Uint16 iterations(complex z);
    void populateGrid();
    void resizeGrid(Uint16 h, Uint16 w);
    Uint16 getGridAt(Uint16 y, Uint16 x);
    Uint16* getGrid();
    Uint16 getHeight() { return height; }
    Uint16 getWidth() { return width; }
    std::string toString();
    std::string toString(Uint16 chrs);
private:
    int charSize = 10;
    char chars[10] = { '@', '.', '$', ',', '&', '-', '#', ' ', '+', '*'};
    complex topleft;
    complex bottomright;
    Uint16 maxiter;
    Uint16* grid;
    Uint16 width;
    Uint16 height;
};

#endif /* mandelbrot_hpp */
