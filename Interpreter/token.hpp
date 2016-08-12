/*** token.hpp
 * This file defines the token class. This will be used by the interpreter
 * class along with the parser and lexer classes, found in Interpreter
 * directory. */
#ifndef token_hpp
#define token_hpp
#include <string>
#include <sstream>


enum class TOKEN {
	NONE = 0,	// Error
	EoF,		// End of input stream
	NEWLINE,	// '\n'

	LBRACE,		// '{'
	RBRACE,		// '}'
	LPAREN,		// '('
	RPAREN,		// ')'
	LBRACK,		// '['
	RBRACK,		// ']'
	LANGLE,		// '<'
	RANGLE,		// '>'
	BSLASH,		// '\'
	FSLASH,		// '/'
	PIPE,		// '|'
// Operators	
	EQUAL,		// '='
	EQUALITY,	// '=='
	ADD,		// '+'
	SUBTRACT,	// '-'
	MULTIPLY,	// '*'
	DIVIDE, 	// '/'
	INCR,		// "++"
	DECR,		// "--"
	PLUSEQ,		// "+="
	MINUSEQ,	// "-="
	MULTEQ,		// "*="
	DIVEQ,		// "/="
	POWER,		// '**'
	ELIPSES,	// '..'
	DOT,		// '.'
	// Punctuation
	SEMICOLON,	// ';'
	QUOTE,		// '"'
	APOSTROPHE,	// "'"
// Keywords
	LET,		// let: assignment `let x = 2`
	VAR,		// variable

	IF,			// if (x == blah)
	FOR,		// for loops
	WHILE,		// while loops

	CREATE,		// create command
	REMOVE,		// remove command
	INFO,		// dump info on object
	LS,			// list current objects
	VIEW,		// view an object (viewable only) - render to screen
	INIT,		// initialize an object
	LOAD,		// load from file/stream
	SAVE,		// save to disk

	MANDELBROT,	// mandelbrot object
	JULIA,		// julia object
// Types
	CHAR,
	INT,
	UINT,
	STRING,
	FLOAT,
	IMAG,

	MAX_TOKEN	// Sentinal Token
};

class token{
public:
	token(){ 
		type = TOKEN::NONE;
		text = "NONE";
	}

	token(TOKEN type, std::string text);

	TOKEN type;
	std::string text;
	std::string get_str();
	int get_int();
	double get_float();
	

	std::string toString();

};
#endif
