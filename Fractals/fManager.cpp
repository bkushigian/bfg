#include "fManager.hpp"

fManager::fManager(){
	capacity = 8;
	size = 0;
	objects = new object*[capacity];
	current = NULL;
	WM = NULL;
	currentIndex = 0;
}

fManager::~fManager(){
	if (objects != NULL){
		for (int i = 0; i < size; ++i) {
			if (objects[i] != NULL)
				delete objects[i];
		}
		delete[] objects;
	}
}

object* fManager::getCurrent() {
	return current; 
}

object* fManager::get(int n){
	if (0 <= n && n < size) return objects[n];
	return NULL;
}

object* fManager::next() {
	if (size == 0) return NULL;
	std::cout << "FM::next()\n";
	currentIndex = (currentIndex + 1) % size;
	current = objects[currentIndex];
	if (current == NULL) std::cout << "FM::current == NULL\n";
	else std::cout << "FM::Current != NULL\n";
	return current;
}

object* fManager::prev() {
	if (size == 0) return NULL;
	currentIndex = (currentIndex - 1) % size;
	current = objects[currentIndex];
	return current;
}

object* fManager::add(object* f){
	// Initialize f
	if (f->getObjectType() == OBJ_DRAWABLE){
		dynamic_cast<fractal*> (f)->setWM(WM);
		f->init();
	}
	
	// If we are out of room...
	if (size == capacity ) {
		object** fs = new object*[capacity * 2];
		for (int i = 0; i < capacity; ++i) {
			fs[i] = objects[i];
		}
		for (int i = capacity; i < capacity * 2; ++i){
			fs[i] = NULL;
		}
		fs[size] = f;
		capacity *= 2;
		++size;
		delete[] objects;
		objects = fs;
		if (current == NULL) current = objects[size - 1];
		return f;
	}
	// Otherwise...
	objects[size++] = f;
	if (current == NULL) current = objects[size - 1];
	return f;
}
int fManager::remove(){
	if (current == NULL) return -1;
	if (size == 0) return -1;

	delete current;
	for (int i = currentIndex + 1; i < size; ++i){
		objects[i-1] = objects[i];
	}
	--size;
	return 0;
}

int fManager::remove(int n){
	if (n < 0 || n >= size) return -1;
	if (objects[n] == NULL) return -1;
	delete objects[n];
	for (int i = n+1; i < size; ++i){
		objects[i-1] = objects[i];
	}
	--size;
	return 0;
}

void fManager::reset(){
	while (size > 0){
		if (objects[size-1] != NULL)
			delete objects[size-1];
		--size;
	}
}

void fManager::draw(){
	std::cout << "FM.draw()\n";
	std::cout << (unsigned long int) current << std::endl;
	if (current != NULL)
		current->draw();
	
}
