//
//  julia.cpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/9/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#include "julia.hpp"



julia::julia(){
	mode = RNDR_PIXARRAY;
    topleft = complex(-2.0,2.0);
    bottomright = complex(2.0,-2.0);
    C = complex(.5, .5);
    maxiter = 60; width = 70; height = 50;
    grid = new Uint16[height * width];

	chars = "@.$,&-# +*";	
	charSize = 10;

	name = "Julia";
	type = JULIA_T;
	mode = RNDR_PIXARRAY;
}

julia::julia(cmplx tl, cmplx br, Uint16 height, Uint16 width, Uint16 max){
	mode = RNDR_PIXARRAY;
    topleft = tl; bottomright = br;
    this->width = width; this->height = height;
    C = complex(.5, .5);
    maxiter = max;
    grid = new Uint16[height * width];
	
	chars = "@.$,&-# +*";	
	charSize = 10;
	name = "Julia";
	type = JULIA_T;
	mode = RNDR_PIXARRAY;
}

julia::~julia(){
    delete[] grid;
}

Uint16 julia::iterations(complex z) {
    Uint16 iterations = 0;
    while (++iterations < maxiter && z.squaremodulus() < 4){
        z = z*z + C;
    }
    return iterations;
}

void julia::populateGrid(){
    double deltaX = (bottomright - topleft).getRe()/width;
    double deltaY = (topleft - bottomright).getIm()/height;
    for (Uint32 i = 0; i < height*width; ++i){
		grid[i] = iterations(topleft - deltaY*(i/width)*unitIm + deltaX*(i % width)*unitRe);
    }
}

/*void julia::resizeGrid(Uint16 h, Uint16 w){
    Uint16* newGrid = new Uint16[h*w];
    for (int i = 0; i < h*w; ++i)
}*/

Uint16 julia::getGridAt(Uint16 x, Uint16 y){
    if (y < height && x < width)
        return grid[x + width * y];
    return 0;
}

Uint16* julia::getGrid(){
    return grid;
}

std::string julia::toString(){
    return toString(2);
}
std::string julia::toString(Uint16 chrs){
    if (chrs > 10) chrs = 10;
    std::ostringstream ss;
    for (Uint16 j = 0; j < height; ++j){
        for (Uint16 i = 0; i < width; ++i){
            ss << chars[grid[i + height*j ] % chrs];
        }
        ss << '\n';
    }
    return ss.str();
}
