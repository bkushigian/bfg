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
	"**",
	"..",

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

	"MAX_TOKEN"
};

//constructor
token::token(int type, std::string text){
	this->type = type;
	this->text = text;
}

std::string token::toString(){
	return "<'" + text + "','" + tokenNames[type] + ">";
}
