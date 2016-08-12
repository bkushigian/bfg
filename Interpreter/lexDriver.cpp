/* parserDriver - to test parsing functionality
 * Compiles with:
g++-5 -std=c++14 parserDriver.cpp parser.cpp lexer.cpp token.cpp statement.cpp -o parserDriver
 * */
#include <iostream>
#include "token.hpp"
#include "parser.hpp"
#include "lexer.hpp"
#include <vector>

using namespace std;

int main(int argc, char** argv){
	std::string input_strings[] = {
		"let z = 5 + 3.2i", 
		"let m = mandelbrot", 
		"3 + 5i",
		"x = 7 / 2",
		"x += 2",
		"print x"
	};
	parser p;
}
