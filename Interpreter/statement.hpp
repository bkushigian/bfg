#ifndef statement_hpp
#define statement_hpp

#include "expr.hpp"
#include <vector>

enum class STMNT {		// Types of statements
	NONE,				// No statement
	EMPTY,				// Empty statement
	IF,					// if
	ELIF,				// else if
	ELSE,				// else
	WHILE,				// while
	FOR,				// for
	EXPR,				// expression
	EXPR_BOOL,			// EXPR_BOOL
	EXPR_INT,			// EXPR_INT
	EXPR_FLOAT,			// EXPR_FLOAT
	EXPR_COMPLEX,		// EXPR_COMPLEX
	EXPR_CHAR,			// EXPR_CHAR
	EXPR_STRING,		// EXPR_STRING
	EXPR_OTHER			// EXPR_OTHER
};

class statement{
private:

public:
	STMNT type;
};

class ifstatement : public statement{
private:
	expr condition;				// Must be bool or integral
	std::vector<expr> stmnts;	// Statements to execute
public:
	ifstatement();
};
#endif

