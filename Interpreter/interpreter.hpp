/*** interpreter.hpp
 * This file defines the interpreter class. This will be used to interpret
 * command line and source files written in BFGlang ***/

#ifndef interpreter_hpp
#define interpreter_hpp


#include <string>
#include <sstream>
#include <vector>
#include "../Fractals/fManager.hpp"
#include "../Fractals/julia.hpp"
#include "../Globals/globals.hpp"

#include <unordered_map>
// Parser/Lexer/Tokens
#include "parser.hpp"

class interpreter : public object {
private:
	fManager* FM;
	winManager* WM;
	std::string* history;
public:
	interpreter();
	interpreter(fManager* fm);
	interpreter(fManager* fm, winManager* wm);
	int parse(std::string c);
};

class tokenizer{

};
#endif
