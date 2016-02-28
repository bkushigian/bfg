#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <string>
#include <sstream>
#include <stdio.h>
#include <SFML/Config.hpp>
#include <complex>
#include "../Globals/globals.hpp"
#include "object.hpp"

class winManager;



class fractal : public object{

protected:
	DSP_MODE displayMode;
	std::string name;
	FRACTAL_TYPE type;
	winManager* WM;
	bool populated;

public:
	fractal() {
		displayMode = DSP_NONE;
		type = FT_NONE;
		objectType = OBJ_DRAWABLE;
	}
	virtual void init(){} 
	virtual sf::Uint16* getGrid() {return NULL;}
	virtual std::string getName() { return "Generic Fractal"; }
	virtual FRACTAL_TYPE getType() { return FT_NONE; }
	virtual DSP_MODE  getDisplayMode() { return DSP_NONE; }
	virtual void setName(std::string n){}
	// Return string of info on fractal;
	virtual std::string info(){ return name;}
	virtual void setWM(winManager* wm) { WM = wm; } // Set window manager
	virtual void draw(){};
	virtual int handleEvent(char event) {return 0;}
	virtual int rightClick(int x, int y){return 0;}
	virtual int leftClick (int x, int y){return 0;}

	virtual bool isPopulated(){ return populated; }

};

#endif
