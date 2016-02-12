/* Compile with
	g++ -c winManager.cpp ../math/complex.cpp ../Fractals/mandelbrot.cpp ../Fractals/julia.cpp ../Fractals/fManager.cpp -lsfml-system -lsfml-graphics -lsfml-window
*/
#ifndef WIN_MANAGER_HPP
#define WIN_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include "../Globals/globals.hpp"			// Global Variables

#include "../math/complex.hpp"

#include "../Fractals/mandelbrot.hpp"
#include "../Fractals/julia.hpp"
#include "../Fractals/fractal.hpp"
#include "../Fractals/fManager.hpp"
using namespace sf;

// winManager - handles windows, runs main loop
class winManager{
private:
	
// Variables
	Uint16 WIDTH, HEIGHT, MAX_ITERS;
	fManager FM;
	DSP_MODE displayMode;
	Uint8 *pixArray;

// Private Functions
	void setPixArray(Uint8* pix, int width, int height);
	void setPixArray(Uint8* pix, Uint16* grid, int width, int height);
	int handleEvent(Event event);
	
public:
	winManager();
	void mainLoop();
	void addFractal(fractal* f);
	void setDisplayMode(DSP_MODE dm){ displayMode = dm; }
};

#endif
