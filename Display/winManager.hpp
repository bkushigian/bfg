#ifndef WIN_MANAGER_HPP
#define WIN_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include "../math/complex.hpp"
#include "../Fractals/mandelbrot.hpp"
#include "../Fractals/julia.hpp"
#include "../Fractals/fractal.hpp"
#include "../Fractals/fManager.hpp"

using namespace sf;

enum EVENT_HANDLE_MODE {HNDL_NONE, HNDL_NORMAL, HNDL_CMND};
// winManager - handles windows, runs main loop
class winManager{
private:
	Uint16 WIDTH, HEIGHT, MAX_ITERS;
	int handelEvent(Event event);
	fManager FM;
	void setPixArray(Uint8* pix, int width, int height);
	void setPixArray(Uint8* pix, Uint16* grid, int width, int height);

public:
	void mainLoop();
};

#endif
