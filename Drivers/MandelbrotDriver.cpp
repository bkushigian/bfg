
/* compile with
g++ -std=c++11 -o ../bin/MandelbrotDriver.out MandelbrotDriver.cpp ../Fractals/mandelbrot.cpp ../Fractals/complex.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/


#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include "../Fractals/complex.hpp"
#include "../Fractals/mandelbrot.hpp"
//#include "../Display/display.hpp"
#include <fstream>

using namespace std;
using namespace sf;
int WIDTH = 1000, HEIGHT = 1000;
mandelbrot m(complex(-2,2), complex(2,-2),HEIGHT,WIDTH,256);

int handleEvent(Event event);
void renderingThread(sf::Window* window);
void setPixArray(Uint8* pix, unsigned int** grid, int width, int height);
void populateSubArr(Uint8** arrs, int tmin, int tmax);
int runWindow();

int main(){
    // main window                           (width/height)
    runWindow();
    return 0;
}

int runWindow(){
	/* Create Window */
    RenderWindow winMain(VideoMode(WIDTH, HEIGHT), "OpenGL");
	/* Clear/Display black */
    winMain.clear(Color::Black);
    winMain.display();
	/* Populate Grid, Set up arr */
    m.populateGrid();
    // Setup Arr
    Uint8 arr[WIDTH * HEIGHT * 4];
	setPixArray(arr, m.getGrid(), WIDTH, HEIGHT);
	/* image/texture for display */
    Image image;
    Texture texture;

	image.create(WIDTH, HEIGHT, arr);
	if (!texture.create(WIDTH,HEIGHT)) return -1;
	texture.update(image);
	Sprite sprite(texture);

    while (winMain.isOpen())
    {

        //std::cout << "polling events\n";
        Event event;
        while(winMain.pollEvent(event))
        {
            if (handleEvent(event) == 1) winMain.close();
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
            return 0;
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

void setPixArray(Uint8* pix, unsigned int** grid, int width, int height){
    for (int j = 0; j < height; ++j){
        for (int i = 0; i < width; ++i){
            pix[width * 4 * j + 4 * i] = (15 * grid[j][i]) % 128;
            pix[width * 4 * j + 4 * i + 1] = (11 * grid[j][i]) % 128;
            pix[width * 4 * j + 4 * i + 2] = (18 * grid[j][i]) % 128;
            pix[width * 4 * j + 4 * i + 3] = 255;
        }
    }
}
