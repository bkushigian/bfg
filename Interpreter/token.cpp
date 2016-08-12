#include "token.hpp"


// tokenNames

const std::string tokenNames[] = {
	"NONE",
	"EoF",
	"NEWLINE",

	"LBRACE",
	"RBRACE",
	"LPAREN",
	"RPAREN",
	"LBRACK",
	"RBRACK",
	"LANGLE",
	"RANGLE",
	"BSLASH",
	"FSLASH",
	"PIPE",
	
	"=",
	"==",
	"+",
	"-",
	"*",
	"/",
	"++",
	"--",
	"+=",
	"-=",
	"*=",
	"/=",
	"**",
	"..",
	".",

	";",
	"\"",
	"'",

	"let",
	"VAR",

	"if",
	"for",
	"while",

	"create",
	"remove",
	"info",
	"ls",
	"view",
	"init",
	"load",
	"save",

	"mandelbrot",
	"julia",

	"char",
	"int",
	"uint",
	"string",
	"float",
	"imag",

	"MAX_TOKEN"
};

//constructor
token::token(TOKEN type, std::string text){
	this->type = type;
	this->text = text;
}

std::string token::toString(){
	return "<'" + text + "', " + tokenNames[static_cast<int>(type)] + " >";
}
std::string token::get_str(){
	return text;
}
int token::get_int(){
	if (type == TOKEN::INT){
		return std::atoi(text.c_str());
	}
	if (type == TOKEN::FLOAT){		// Truncates... Should error handle
		return std::atoi(text.c_str());
	}
	return 0;			// Error handling ...
}
double token::get_float(){
	if (type == TOKEN::FLOAT) return std::atof(text.c_str());
	return 0;
}
