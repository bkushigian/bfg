#ifndef FRACTAL_MANAGER_HPP
#define FRACTAL_MANAGER_HPP

#include <string>
#include <iostream>
#include "fractal.hpp"
#include "../Globals/globals.hpp"



class winManager;

class fManager{
public:
	fManager();
	~fManager();
	fractal* getCurrent() {return current; }
	int getSize() { return size; }
	int getCapacity() { return capacity; }
	fractal* get(int n);
	fractal* next();
	fractal* prev();
	fractal*  add(fractal* f);
	fractal* remove(){ return NULL; }
	fractal* remove(int n){ return NULL; }
	void setWM(winManager* wm) { WM = wm; }

	void draw();		// Current fractal draws

private:
	int capacity;
	int size;
	fractal** fractals; // Array of Fractal pointers
	fractal* current; 	// Pointer to current fractal
	int currentIndex;
	winManager* WM;

};

#endif
