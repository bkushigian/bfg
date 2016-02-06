/* compile with
g++ -std=c++11 -o bin/main.out main.cpp Fractals/julia.cpp Fractals/mandelbrot.cpp Fractals/complex.cpp Display/display.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/


#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include "Fractals/complex.hpp"
#include "Fractals/julia.hpp"
#include "Fractals/mandelbrot.hpp"
#include "Display/display.hpp"
#include "Display/Button.hpp"
#include <fstream>

using namespace std;
using namespace sf;
int WIDTH = 1000, HEIGHT = 1000;
int sleepTime = 15;
mandelbrot m(complex(-2,2), complex(2,-2),HEIGHT,WIDTH,256);
julia j(complex(-2,2), complex(2,-2), HEIGHT, WIDTH, 128);

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

void populateSubArr(Uint8** arrs, int tmin, int tmax, int jIters){
    complex C(0,0);
    julia J(complex(-2,2), complex(2,-2), HEIGHT, WIDTH, 128);
    for (int t = tmin; t < tmax; ++t){
        C.setRe(1.1*cos(2*3.14159256*(double)t/4000) + .8*cos(8*3.1415926535*(double)t/jIters));
        C.setIm(1.2*sin(2*3.14159256*(double)t/4000) + .85*sin(10*3.1415926535*(double)t/jIters));

        J.setC(C);
        J.populateGrid();
        std::cout << "setPixArray " << t << "\n";
        setPixArray(arrs[t],J.getGrid(), WIDTH, HEIGHT);
    }
}

int runWindow(){
    std::cout << "Run Window\n";
    RenderWindow winMain(VideoMode(WIDTH, HEIGHT), "OpenGL");
    winMain.clear(Color::Black);
    winMain.display();
    int jIters = 400;
    //m.populateGrid();
    std::cout << "Declaring arrs\n";
    Uint8 **arrs;
    arrs = new Uint8*[jIters];
    for (int i = 0; i < jIters; ++i){
        arrs[i] = new Uint8[1200 * 1500 * 4];
    }
    // Setup Arr
    std::cout << "Making a C\n";
    complex C(0,0);
    int t = 0;
    std::cout << "Setting Up Arrs\n";

    // sf::Thread thread1(std::bind(&populateSubArr, arrs, 0, 300, jIters));
    // thread1.launch();
    // sf::Thread thread2(std::bind(&populateSubArr, arrs, 300, 600, jIters));
    // thread2.launch();
    // sf::Thread thread3(std::bind(&populateSubArr, arrs, 600, 900, jIters));
    // thread3.launch();
    // sf::Thread thread4(std::bind(&populateSubArr, arrs, 900, 1200, jIters));
    // thread4.launch();
    while( t < jIters){
        std::cout << "t = " << t << std::endl;
        C.setRe(1.1*cos(2*3.14159256*(double)t/jIters) + .2*cos(8*3.1415926535*(double)t/jIters));
        C.setIm(1.2*sin(2*3.14159256*(double)t/jIters) + .25*sin(10*3.1415926535*(double)t/jIters));

        j.setC(C);
        j.populateGrid();
        std::cout << "setPixArray\n";
        setPixArray(arrs[t],j.getGrid(), WIDTH, HEIGHT);
        ++t;
    }
    std::cout << "Creating Image\n";
    //Uint8 arr[WIDTH * HEIGHT * 4];
    Image image;
    std::cout << "Creating Texture\n";
    // complex deltaX(0.05, 0);
    // complex deltaY(0, 0.051);
    Texture texture;
    t = 0;
    std::cout << "Main Loop\n";
    while (winMain.isOpen())
    {
        //j.populateGrid();
        //std::cout << "image.create\n";
        image.create(WIDTH, HEIGHT, arrs[t]);
        if (!texture.create(WIDTH,HEIGHT)) return -1;
        texture.update(image);
        Sprite sprite(texture);

        //std::cout << "polling events\n";
        Event event;
        while(winMain.pollEvent(event))
        {
            if (handleEvent(event) == 1) winMain.close();
        }
        winMain.clear(Color::Black);
        winMain.draw(sprite);

        winMain.display();
        // if (j.getC().getRe() < -2.0 || j.getC().getRe() > 2.0){
        //     deltaX = deltaX * -1.0;
        // }
        // if (j.getC().getIm() < -2.0 || j.getC().getRe() > 2.0){
        //     deltaY = deltaY * -1.0;
        // }
        // j.setC(j.getC() + deltaX + deltaY);
        ++t;
        t %= jIters;
        sf::sleep(sf::milliseconds(sleepTime));
    }
    for (int i = 0; i < 100; ++i){
        delete arrs[i];
    }
    delete arrs;

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
            if (event.mouseButton.button == Mouse::Right){
                sleepTime += 5;
                std::cout << "Sleeptime = " << sleepTime << std::endl;
            }
            else if (event.mouseButton.button == Mouse::Left){
                sleepTime -= 5;
                std::cout << "Sleeptime = " << sleepTime << std::endl;
                // cout << "left-click" << endl;
                // cout  << "mouse pos: (" << event.mouseButton.x << ','
                // << event.mouseButton.y << ")\n";
            }
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
