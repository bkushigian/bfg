/* Compile with
	g++ -c winManager.cpp ../Fractals/mandelbrot.cpp ../Fractals/julia.cpp ../Fractals/fManager.cpp -lsfml-system -lsfml-graphics -lsfml-window
*/
#ifndef WIN_MANAGER_HPP
#define WIN_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "../Globals/globals.hpp"			// Global Variables
#include <complex>
#include "../Fractals/mandelbrot.hpp"
#include "../Fractals/julia.hpp"
#include "../Fractals/fractal.hpp"
#include "../Fractals/factory.hpp"
#include "commandLine.hpp"



class fManager;
#include "../Fractals/fManager.hpp"
// winManager - handles windows, runs main loop
class winManager{
private:
	
// Variables
	Uint16 WIDTH, HEIGHT, MAX_ITERS;
	fManager FM;
	DSP_MODE displayMode;
	Uint8 *pixArray;
	commandLine command;
	bool commandMode;

	sf::Text commandText;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow winMain;
	sf::Font font;
	int fontSize;	// commandline font size
	int lineSpace;	// Pixels after line in cmndline
// Private Functions
	int handleEvent(sf::Event event);
	int handleNormalEvent(sf::Event event);
	int handleCmndEvent(sf::Event event);

	void positionText(sf::Text& t, int n);
	void positionText(sf::Text& t);
	
public:
	winManager();
	~winManager();
	void mainLoop();
	void addFractal(fractal* f);
	void setDisplayMode(DSP_MODE dm){ displayMode = dm; }
	void setPixArray(Uint16* pix, int width, int height);
	void setPixArray(Uint8* pix, Uint16* grid, int width, int height);
	void toggleCmnd() {displayMode = displayMode ^ DSP_CMND;}
};

#endif
