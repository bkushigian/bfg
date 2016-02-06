//
//  mandelbrot.cpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/8/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#include "mandelbrot.hpp"


mandelbrot::mandelbrot(){
    topleft = complex(-2.0,2.0);
    bottomright = complex(2.0,-2.0);
    maxiter = 60; width = 70; height = 50;
    grid = new Uint16[height * width];
}

mandelbrot::mandelbrot(cmplx tl, cmplx br, Uint16 height, Uint16 width, Uint16 max){
    topleft = tl; bottomright = br;
    this->width = width; this->height = height;
    maxiter = max;
    grid = new Uint16[width * height];
}

mandelbrot::~mandelbrot(){
    delete[] grid;
}

Uint16 mandelbrot::iterations(complex z) {
    complex C = z;
    Uint16 iterations = 0;
    while (++iterations < maxiter && z.squaremodulus() < 4){
        z = z*z + C;
    }
    return iterations;
}

void mandelbrot::populateGrid(){
    double deltaX = (bottomright - topleft).getRe()/width;
    double deltaY = (topleft - bottomright).getIm()/height;
    for (Uint32 i = 0; i < width * height; ++i){
		grid[i] = iterations(topleft - deltaY*(i/height)*unitIm + deltaX*(i%width)*unitRe);
    }
}
/*
void mandelbrot::resizeGrid(Uint16 h, Uint16 w){
    Uint16** newGrid = new Uint16*[h];
    for (int i = 0; i < h; ++i)
        newGrid[i] = new Uint16[w];
    height = h; width = w;
}
*/
Uint16 mandelbrot::getGridAt(Uint16 x, Uint16 y){
    if (y < height && x < width)
        return grid[x + width*y];
    return 0;
}
Uint16* mandelbrot::getGrid(){
    return grid;
}

std::string mandelbrot::toString(){
    return toString(2);
}
std::string mandelbrot::toString(Uint16 chrs){
    if (chrs > 10) chrs = 10;
    std::ostringstream ss;
    for (Uint16 j = 0; j < height; ++j){
        for (Uint16 i = 0; i < width; ++i){
            ss << chars[grid[i + j * width] % chrs];
        }
        ss << '\n';
    }
    return ss.str();
}
