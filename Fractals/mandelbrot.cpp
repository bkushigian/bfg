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
    grid = new sf::Uint16[height * width];
	chars = "@.$,&-# +*";	
	charSize = 10;
	name = "Mandelbrot";
	type = FT_MANDEL;
	displayMode = DSP_PIXARRAY;
}

mandelbrot::mandelbrot(cmplx tl, cmplx br, sf::Uint16 height, sf::Uint16 width, sf::Uint16 max){
    topleft = tl; bottomright = br;
    this->width = width; this->height = height;
    maxiter = max;
    grid = new sf::Uint16[width * height];

	chars = "@.$,&-# +*";	
	charSize = 10;
	name = "Mandelbrot";
	type = FT_MANDEL;
	displayMode = DSP_PIXARRAY;
}

mandelbrot::~mandelbrot(){
    delete[] grid;
}

sf::Uint16 mandelbrot::iterations(complex z) {
    complex C = z;
    sf::Uint16 iterations = 0;
    while (++iterations < maxiter && z.squaremodulus() < 4){
        z = z*z + C;
    }
    return iterations;
}

void mandelbrot::populateGrid(){
    double deltaX = (bottomright - topleft).getRe()/width;
    double deltaY = (topleft - bottomright).getIm()/height;
    for (sf::Uint32 i = 0; i < width * height; ++i){
		grid[i] = iterations(topleft - deltaY*(i/height)*unitIm + deltaX*(i%width)*unitRe);
    }
}
/*
void mandelbrot::resizeGrid(sf::Uint16 h, sf::Uint16 w){
    sf::Uint16** newGrid = new sf::Uint16*[h];
    for (int i = 0; i < h; ++i)
        newGrid[i] = new sf::Uint16[w];
    height = h; width = w;
}
*/
sf::Uint16 mandelbrot::getGridAt(sf::Uint16 x, sf::Uint16 y){
    if (y < height && x < width)
        return grid[x + width*y];
    return 0;
}
sf::Uint16* mandelbrot::getGrid(){
    return grid;
}

std::string mandelbrot::toString(){
    return toString(2);
}
std::string mandelbrot::toString(sf::Uint16 chrs){
    if (chrs > 10) chrs = 10;
    std::ostringstream ss;
    for (sf::Uint16 j = 0; j < height; ++j){
        for (sf::Uint16 i = 0; i < width; ++i){
            ss << chars[grid[i + j * width] % chrs];
        }
        ss << '\n';
    }
    return ss.str();
}
