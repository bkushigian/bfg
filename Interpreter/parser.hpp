/*** parser.hpp
 * Defines the parser class. To be used by the interpreter class, found in     
 * Interpreter/interpreter.hpp. */

#ifndef parser_hpp
#define parser_hpp

#include "token.hpp"
#include "lexer.hpp"
#include <vector>
#include <string>

class parser{
private:
	parser();
	lexer lex;
	std::vector<token> vec_t;
	int index;				// For vec_t
	//std::vector<std::string> vec_s;		// MAYBE??
public:
	void set_input(std::string s);		// Pass to lex; append to vec_t

};
#endif
