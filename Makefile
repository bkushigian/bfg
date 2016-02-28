CC=g++-5
CFLAGS=-std=c++14 -Wall -g -o bfg
LINKS=-lsfml-system -lsfml-graphics -lsfml-window
main: main.o julia.o mandelbrot.o winManager.o \
	commandLine.o fManager.o 
	$(CC) $(CFLAGS) main.o julia.o mandelbrot.o winManager.o \
	commandLine.o fManager.o $(LINKS)

main.o: main.cpp Globals/globals.hpp Fractals/fractal.hpp Fractals/mandelbrot.hpp \
	Fractals/julia.hpp Display/winManager.hpp
	$(CC) -std=c++14 -c main.cpp

julia.o: Fractals/julia.cpp Fractals/fractal.hpp Display/winManager.hpp \
	Globals/globals.hpp Fractals/julia.hpp
	$(CC) -std=c++14 -c Fractals/julia.cpp

mandelbrot.o: Globals/globals.hpp Fractals/fractal.hpp Display/winManager.hpp \
	Fractals/factory.hpp Fractals/mandelbrot.hpp
	$(CC) -std=c++14 -c Fractals/mandelbrot.cpp

winManager.o: Globals/globals.hpp Fractals/fractal.hpp Fractals/mandelbrot.hpp \
	Fractals/julia.hpp Fractals/factory.hpp Display/commandLine.hpp \
	Display/winManager.hpp
	$(CC) -std=c++14 -c Display/winManager.cpp

commandLine.o: Display/commandLine.cpp Display/commandLine.hpp
	$(CC) -std=c++14 -c Display/commandLine.cpp

fManager.o: Fractals/fManager.cpp Fractals/fractal.hpp Fractals/object.hpp \
	Globals/globals.hpp Fractals/fManager.hpp
	$(CC) -std=c++14 -c Fractals/fManager.cpp

clean: 
	rm main.o julia.o mandelbrot.o winManager.o commandLine.o fManager.o

clean-all: 
	rm bfg main.o julia.o mandelbrot.o winManager.o commandLine.o fManager.o

