#ifndef lexer_hpp
#define lexer_hpp
#include "token.hpp"
#include <string>
#include <sstream>
#include <ctype.h>

class lexer{
private:
	std::string input;		// Input
	std::string buffer;		// For returning extra data
	long long int buf_int;	// For returning integers
	double buf_dbl;			// For returning doubles
	char c;
	size_t size;	// string size
	unsigned long long index;	// Index of current token
	unsigned long long p;		// Set to point to substr start
public:
	lexer();
	token next_token();
	void set_input(std::string str);
	void clear_buffer();
	std::string get_buffer();
	void append_buffer();
	/*** return -1 if not valid ***/
	char consume();		// progress in input, return new character pointed at
	char vomit();		// Backup in input, return character last consumed
	char peek();
	char peek(int n);
	bool match(char ch);


	bool consume_alpha();
	bool consume_digit();
	bool consume_alnum();
	bool consume_name();
	int consume_number();
};
#endif
