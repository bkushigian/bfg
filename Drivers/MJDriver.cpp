/* compile with
g++ -std=c++11 -o ../bin/MJDriver.out MJDriver.cpp ../Fractals/julia.cpp ../Fractals/mandelbrot.cpp ../Fractals/fManager.cpp ../math/complex.cpp -lsfml-graphics -lsfml-window -lsfml-system 
*/


#include <iostream>
#include <math.h>
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
//#include "../Display/display.hpp"
#include <fstream>

using namespace std;
using namespace sf;

/* Global Variables */

// Window Dimensions
Uint16 WIDTH = 1000, HEIGHT = 1000;
Uint16 MAX_ITERS = 255;

complex tl(-2.0, 2.0);
complex br(2.0, -2.0);
// Fractal Instances
fractal* f_ptr;			// Generic Fractal Pointer
fManager FM;			// Fractal Manager


/* Function Declarations */

int handleEvent(Event event);
void renderingThread(sf::Window* window);
int runWindow();
void setPixArray(Uint8* pix, int width, int height);
void setPixArray(Uint8* pix, Uint16* grid, int width, int height);
/*** MAIN ***/

int main(){
	std::cout << "Top Of Main\n";
	std::cout << "Creating mandelbrot\n";
	f_ptr = static_cast<fractal*>(new mandelbrot(tl , br, WIDTH, HEIGHT, MAX_ITERS));
	std::cout << "Storing mandelbrot\n";
   	FM.add(f_ptr);	 
	std::cout << "Creatin and Storing julia\n";
	FM.add(static_cast<fractal*>(new julia(tl, br, WIDTH, HEIGHT, MAX_ITERS)));
	std::cout << "Calling Run Window()\n";
    runWindow();
    return 0;
}


/* Function Definitions */


int runWindow(){

	std::cout << "Creating Window\n";
	/* Create Window */
    RenderWindow winMain(VideoMode(WIDTH, HEIGHT), "Fractals");

	/* Clear/Display black */
    winMain.clear(Color::Black);
    winMain.display();

	/* Populate Grid, Set up arr */
	std::cout << "Populating mandelbrot grid\n";
	FM.get(0)->populateGrid();
	FM.get(1)->populateGrid();
    // Setup Arr
	std::cout << "Declaring arr\n";
    Uint8 arr[WIDTH * HEIGHT * 4]; // Stores Pixels
	std::cout << "Updating arr\n";
	setPixArray(arr, FM.getCurrent()->getGrid(),  WIDTH, HEIGHT);
	
	/* image/texture for display */
    Image image;
    Texture texture;

	image.create(WIDTH, HEIGHT, arr);
	if (!texture.create(WIDTH,HEIGHT)) return -1;
	texture.update(image);
	Sprite sprite(texture);
	std::cout << "Entering Loop\n";
    while (winMain.isOpen())
    {
        Event event;
		int eventNum = 0;
        while(winMain.pollEvent(event))
        {
			eventNum = handleEvent(event);	
            if (eventNum == 1) winMain.close();
			else if (eventNum == 2){
				FM.next();
				setPixArray(arr, FM.getCurrent()->getGrid(), WIDTH, HEIGHT);
				image.create(WIDTH, HEIGHT, arr);
				texture.update(image);
				sprite.setTexture(texture);
			}
			
        }
        winMain.clear(Color::Black);
        winMain.draw(sprite);

        winMain.display();
    }
}
int handleEvent(Event event){
    switch (event.type)
    {
        /* Closed */
        case Event::Closed:
            return 1;
        /* Key Pressed */
        case Event::KeyPressed:
            //cout << "Key Pressed\n";
            return 2;
        /* Resize */
        case Event::Resized:
            //glViewport(0, 0, event.size.width, event.size.height);
            return 0;
        /* Loose Focus */
        case Event::LostFocus:
            //std::cout << "lost focus" << std::endl;
            return 0;
        /* Gained Focus */
        case Event::GainedFocus:
            //std::cout << "gained focus" << std::endl;
            return 0;
        /* Mouse Wheel Scroll */
        case Event::MouseWheelScrolled:
            // if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
            //     cout << "wheel type: vertical" << endl;
            // else if (event.mouseWheelScroll.wheel == Mouse::HorizontalWheel)
            //     cout << "wheel type: horizontal" << endl;
            // else
            //     cout << "wheel type: unknown" << endl;
            //     cout << "wheel movement: " << event.mouseWheelScroll.delta << endl;
            //     cout << "mouse x: " << event.mouseWheelScroll.x << endl;
            //     cout << "mouse y: " << event.mouseWheelScroll.y << endl;
                return 0;
        /* Mouse Button Pressed */
        case Event::MouseButtonPressed:
            return 0;
        /* Mouse Moved */
        case Event::MouseMoved:
            // cout  << "mouse pos: (" << event.mouseMove.x << ',' << event.mouseMove.y << ")\n";
            return 0;
        case Event::MouseEntered:
            // cout << "mouse entered window\n";
            return 0;
        case Event::MouseLeft:
            // cout <<"mouse left window\n";
            return 0;
        default:
            return 0;
    }
}



void setPixArray(Uint8* pix, Uint16* grid, int width, int height){
    for (int i = 0; i < height*width; ++i){
		pix[4*i] = (15 * grid[i]) % 256;
		pix[4*i+1] = (11 * grid[i]) % 256;
		pix[4*i+2] = (18 * grid[i]) % 256;
		pix[4*i + 3] = 255;
    }
}

void setPixArray(Uint8* pix, int width, int height){
	Uint16* grid = FM.getCurrent()->getGrid(); for (int i = 0; i < height*width; ++i){
		pix[4*i] = (15 * grid[i]) % 256;
		pix[4*i+1] = (11 * grid[i]) % 256;
		pix[4*i+2] = (18 * grid[i]) % 256;
		pix[4*i + 3] = 255;
	}
}
