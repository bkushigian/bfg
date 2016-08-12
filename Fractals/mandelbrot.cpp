//
//  mandelbrot.cpp
//  Fractals
//
//  Created by Benjamin Kushigian on 1/8/16.
//  Copyright © 2016 Benjamin Kushigian. All rights reserved.
//

#include "mandelbrot.hpp"

/*** mandelbrot class implementation ***/
mandelbrot::mandelbrot(){
  topleft = cmplx(-2.0,2.0);
  bottomright = cmplx(2.0,-2.0);
  maxiter = 60; width = 70; height = 50;
  grid = new sf::Uint16[height * width];
	chars = "@.$,&-# +*";	
	charSize = 10;
	name = "Mandelbrot";
	type = FT_MANDEL;
	displayMode = DSP_PIXARRAY;
	populated = false;
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
	populated = false;
}

mandelbrot::~mandelbrot(){
	if (grid != NULL)
		delete[] grid;
}

sf::Uint16 mandelbrot::iterations(cmplx z) {
    cmplx C = z;
    sf::Uint16 iterations = 0;
    while (++iterations < maxiter && std::abs(z) < 2){
        z = z*z + C;
    }
    return iterations;
}

void mandelbrot::init(){
	populated = true;
  double deltaX = (bottomright - topleft).real()/width;
  double deltaY = (topleft - bottomright).imag()/height;
  for (sf::Uint32 i = 0; i < width * height; ++i){
    grid[i] = iterations( topleft + cmplx(deltaX*(i%width), -deltaY*(i/height)) );
  }
}

void mandelbrot::draw(){
	if (WM == NULL) return;
	std::cout << "Drawing Mandelbrot\n";
	std::cout << "setDisplay\n";
	WM->setDisplayMode(displayMode);
	std::cout << "setPixArray\n";
	WM->setPixArray( grid, width, height);
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
void mandelbrot::zoomin(){
  cmplx center = (topleft + bottomright)/2.0;
  topleft = (topleft - center)*0.8;
  bottomright = (bottomright - center) * 0.8;
  init();
  draw();
}
/*** mandelbrotFactory ***/
mandelbrotFactory::mandelbrotFactory(){
		tl = cmplx(-2.0, 2.0); 
		br = cmplx(2.0, 2.0); 
		maxiter = 255; 
		width = 1000; height = 1000;
}

object* mandelbrotFactory::create(){
	return new mandelbrot(tl, br, height, width, maxiter);
}

int mandelbrotFactory::set(valuePair vp){
	std::string s = vp.name;
	VP_TYPE t = vp.type;
	if (s.compare("topleft") == 0 || s.compare("tl") == 0){
		if (t == CMPLX){
			tl = vp.getComplex();
			return 0;
		} 
	}

	else if (s.compare("bottomright") == 0 || s.compare("br") == 0){
		if (t == CMPLX){
			br = vp.getComplex();
			return 0;
		}
	}

	else if (s.compare("max") == 0 
			|| s.compare( "maxIter") == 0 
			|| s.compare( "maxiter") == 0){
		if (t == UI8 || t == UI16 || t == UI32 || t == UI64){
			maxiter = vp.getUI32();
			return 0;
		}
	}
	else if (s.compare( "width") == 0 || s.compare("w") == 0){
		if (t == UI8 || t == UI16 || t == UI32 || t == UI64){
			width = vp.getUI32();
			return 0;
		}
	}
	else if (s.compare("height") == 0 || s.compare("h") == 0){
		if (t == UI8 || t == UI16 || t == UI32 || t == UI64){
			height = vp.getUI32();
			return 0;
		}
	}
	return 1;		// Error
	
}
