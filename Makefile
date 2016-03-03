CC=g++-5
CFLAGS=-std=c++14 -Wall -g 
LINKS=-lsfml-system -lsfml-graphics -lsfml-window
main: main.o julia.o mandelbrot.o winManager.o \
	commandLine.o fManager.o interpreter.o token.o 
	$(CC) $(CFLAGS) -o bfg main.o julia.o mandelbrot.o winManager.o \
	commandLine.o fManager.o interpreter.o token.o  $(LINKS)

main.o: main.cpp Globals/globals.hpp Fractals/fractal.hpp Fractals/mandelbrot.hpp \
	Fractals/julia.hpp Display/winManager.hpp
	$(CC) $(CFLAGS) -c  main.cpp

julia.o: Fractals/julia.cpp Fractals/fractal.hpp Display/winManager.hpp \
	Globals/globals.hpp Fractals/julia.hpp
	$(CC) $(CFLAGS) -c Fractals/julia.cpp

mandelbrot.o: Globals/globals.hpp Fractals/fractal.hpp Display/winManager.hpp \
	Fractals/factory.hpp Fractals/mandelbrot.hpp
	$(CC) $(CFLAGS) -c Fractals/mandelbrot.cpp

winManager.o: Globals/globals.hpp Fractals/fractal.hpp Fractals/mandelbrot.hpp \
	Fractals/julia.hpp Fractals/factory.hpp Display/commandLine.hpp \
	Display/winManager.hpp
	$(CC) $(CFLAGS) -c Display/winManager.cpp

commandLine.o: Display/commandLine.cpp Display/commandLine.hpp
	$(CC) $(CFLAGS) -c Display/commandLine.cpp

fManager.o: Fractals/fManager.cpp Fractals/fractal.hpp Fractals/object.hpp \
	Globals/globals.hpp Fractals/fManager.hpp
	$(CC) $(CFLAGS) -c Fractals/fManager.cpp

# Interpreter Compilation

interpreter.o: Interpreter/interpreter.cpp Interpreter/token.hpp\
	Interpreter/parser.hpp Interpreter/interpreter.hpp
	$(CC) $(CFLAGS) -c Interpreter/interpreter.cpp

token.o: Interpreter/token.cpp Interpreter/token.hpp
	$(CC) $(CFLAGS) -c Interpreter/token.cpp

#parser.o: Interpreter/parser.cpp Interpreter/parser.hpp Interpreter/token.hpp
#	$(CC) $(CFlAGS) -c Interpreter/parser.cpp

clean: 
	rm main.o julia.o mandelbrot.o winManager.o commandLine.o fManager.o

clean-all: 
	rm bfg main.o julia.o mandelbrot.o winManager.o commandLine.o fManager.o

