#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <string>
#include <sstream>
#include <stdio.h>
#include <SFML/Config.hpp>
#include "../math/complex.hpp"
#include "../Globals/globals.hpp"

class winManager;
class fractal{
protected:
	DSP_MODE displayMode;
	std::string name;
	FRACTAL_TYPE type;
	winManager* WM;

public:
	virtual void populateGrid(){} 
	virtual sf::Uint16* getGrid() {return NULL;}
	virtual int handel(char c) { return 0; }
	virtual std::string getName() { return "Generic Fractal"; }
	virtual FRACTAL_TYPE getType() { return FT_NONE; }
	virtual DSP_MODE  getDisplayMode() { return DSP_NONE; }
	virtual void setName(std::string n){}
	// Return string of info on fractal;
	virtual std::string info(){ return name;}
	virtual void setWM(winManager* wm) { WM = wm; } // Set window manager
	virtual void draw(){};

};

#endif
