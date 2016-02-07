#include "fManager.hpp"

fManager::fManager(){
	capacity = 8;
	size = 0;
	fractals = new fractal*[capacity];
	current = NULL;
	currentIndex = 0;
}

fManager::~fManager(){
	for (int i = 0; i < size; ++i) delete fractals[i];
	delete[] fractals;
}

fractal* fManager::get(int n){
	if (0 <= n && n < size) return fractals[n];
	return NULL;
}

fractal* fManager::next() {
	if (size == 0) return NULL;
	currentIndex = (currentIndex + 1) % size;
	current = fractals[currentIndex];
	return current;
}

fractal* fManager::prev() {
	if (size == 0) return NULL;
	currentIndex = (currentIndex - 1) % size;
	current = fractals[currentIndex];
	return current;
}

fractal* fManager::add(fractal* f){
	// If we are out of room...
	if (size == capacity ) {
		fractal** fs = new fractal*[capacity * 2];
		for (int i = 0; i < capacity; ++i) {
			fs[i] = fractals[i];
		}
		for (int i = capacity; i < capacity * 2; ++i){
			fs[i] = NULL;
		}
		fs[size] = f;
		capacity *= 2;
		++size;
		delete[] fractals;
		fractals = fs;
		if (current == NULL) current = fractals[size - 1];
		return f;
	}
	// Otherwise...
	fractals[size++] = f;
	if (current == NULL) current = fractals[size - 1];
	return f;
}
