#include "fManager.hpp"

fManager::fManager(){
	capacity = 8;
	size = 0;
	fractals = new fractal*[capacity];
	current = NULL;
	WM = NULL;
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
	std::cout << "FM::next()\n";
	currentIndex = (currentIndex + 1) % size;
	current = fractals[currentIndex];
	if (current == NULL) std::cout << "FM::current == NULL\n";
	else std::cout << "FM::Current != NULL\n";
	return current;
}

fractal* fManager::prev() {
	if (size == 0) return NULL;
	currentIndex = (currentIndex - 1) % size;
	current = fractals[currentIndex];
	return current;
}

fractal* fManager::add(fractal* f){
	// Initialize f
	f->setWM(WM);
	f->populateGrid();
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

void fManager::draw(){
	std::cout << "FM.draw()\n";
	std::cout << (unsigned long int) current << std::endl;
	if (current != NULL)
		current->draw();
	
}
