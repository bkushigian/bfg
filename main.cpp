/* compile with
g++-5 -std=c++14 -o bin/main.out main.cpp Fractals/julia.cpp Fractals/mandelbrot.cpp Display/winManager.cpp Fractals/fManager.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <iostream>
#include <math.h>
#include <fstream>
#include <complex>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include "Globals/globals.hpp"
#include "Fractals/fractal.hpp"
#include "Fractals/julia.hpp"
#include "Fractals/mandelbrot.hpp"
#include "Display/winManager.hpp"


using namespace std;
using namespace sf;
int main(){
	winManager WM;
	WM.addFractal(new mandelbrot( 
				-2.0 + 2.0i, 2.0 - 2.0i,
				1000, 1000, 255));
    WM.mainLoop();
    return 0;
}

