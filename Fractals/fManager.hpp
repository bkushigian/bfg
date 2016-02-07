#ifndef FRACTAL_MANAGER_HPP
#define FRACTAL_MANAGER_HPP

#include <string>
#include "fractal.hpp"
#include "mandelbrot.hpp"
#include "julia.hpp"


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
private:
	int capacity;
	int size;
	fractal** fractals; // Array of Fractal pointers
	fractal* current; 	// Pointer to current fractal
	int currentIndex;

};

#endif
