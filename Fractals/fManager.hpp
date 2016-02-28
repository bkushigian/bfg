#ifndef FRACTAL_MANAGER_HPP
#define FRACTAL_MANAGER_HPP

#include <string>
#include <iostream>
#include "object.hpp"
#include "fractal.hpp"
#include "../Globals/globals.hpp"



class winManager;

class fManager{
public:
	fManager();
	~fManager();
	object* getCurrent();
	int getSize() { return size; }
	int getCapacity() { return capacity; }
	object* get(int n);
	object* next();
	object* prev();
	object*  add(object* f);
	int remove();
	int remove(int n);
	void reset();		// Remove all fractals
	void setWM(winManager* wm) { WM = wm; }

	void draw();		// Current object draws

private:
	int capacity;		// Total alloted capacity
	int size;			// Current Size
	object** objects; 	// Array of Fractal pointers
	object* current; 	// Pointer to current object
	int currentIndex;
	winManager* WM;

};

#endif
