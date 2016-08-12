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
#include <complex>
#include "../Globals/globals.hpp"
#include "fractal.hpp"
#include "../Display/winManager.hpp"
#include "factory.hpp"
class winManager;
class mandelbrot: public fractal {
public:
    mandelbrot();
    mandelbrot(cmplx tl, cmplx br, Uint16 height, Uint16 width, Uint16 max);
    ~mandelbrot();
	/* Inherited Functions */

  void init();
	sf::Uint16* getGrid();
	std::string getName() { return name; }
	FRACTAL_TYPE getType() { return type; }
	DSP_MODE getDisplayMode() { return displayMode; }
	void setName(std::string n) { name = n; }
	sf::Uint16 iterations(cmplx z);
  void resizeGrid(Uint16 h, Uint16 w);
	Uint16 getGridAt(Uint16 y, Uint16 x);
	Uint32 getHeight() { return height; }
	Uint32 getWidth() { return width; }
	void draw();
  void zoomin();
  void zoomout();
  void moveup();
  void movedown();
  void moveleft();
  void moveright();
  std::string toString();
  std::string toString(Uint16 chrs);


private:
	std::string chars;
	int charSize;
  cmplx topleft;
  cmplx bottomright;
	Uint16 maxiter;
  Uint16* grid;
  Uint32 width;
  Uint32 height;
	DSP_MODE displayMode;
};


/*** mandelbrotFactory ***/


class mandelbrotFactory: public factory{
private:	
	cmplx tl;
	cmplx br;
	Uint32 maxiter;
	Uint32 width;
	Uint32 height;

public:
	mandelbrotFactory();
	object* create();
	int set(valuePair vp);
};

#endif /* mandelbrot_hpp */
