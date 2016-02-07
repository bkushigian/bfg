#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <string>
#include <sstream>
#include <stdio.h>
#include <SFML/Config.hpp>
#include "../math/complex.hpp"

using namespace sf;
enum FRACTAL_TYPE { NONE_T, JULIA_T, MANDEL_T, NEWTON_T, SIERP_T, };
enum RNDR_MODE {RNDR_NONE, RNDR_TRIANGLES, RNDR_PIXARRAY};
class fractal{
protected:
	RNDR_MODE mode;
	std::string name;
	FRACTAL_TYPE type;
public:
	virtual void populateGrid(){} 
	virtual Uint16* getGrid() {return NULL;}
	virtual int handel(char c) { return 0; }
	virtual std::string getName() { return "Generic Fractal"; }
	virtual FRACTAL_TYPE getType() { return NONE_T; }
	virtual RNDR_MODE  getRenderMode() { return RNDR_NONE; }
	virtual void setName(std::string n){}
	
};

#endif
