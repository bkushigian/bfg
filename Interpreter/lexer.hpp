/*** lexer.hpp
 * Describes the lexer class which parses an input string and transforms into 
 * tokens. Numerical values temporarily stored in buf_int and buf_dbl
 * */

#ifndef lexer_hpp
#define lexer_hpp

#define lexdebug false

#include "token.hpp"
#include <string>
#include <sstream>
#include <ctype.h>
#include <iostream>


/* lexer class
 * Basic mechanism: 
 * 		`c` holds character being processed currently
 * 		index points at character after `c`, i.e. next to be processed.
 * 		Thus when index = input.size() there is 1 character left to process
 * */
class lexer{
private:
	std::string input;		// Input
	std::string buffer;		// For returning extra data

	long long int buf_int;	// For returning integers
	double buf_dbl;			// For returning doubles

	char c;					// Hold character currently being inspected
	size_t size;			// Input size

	unsigned long long index;	// Index of current token
	unsigned long long p;		// Set to point to substr start
	int start;				// Store start of current token
	int end;				// Store end of current token
public:
	lexer();
	token next_token();		// Parse input for next token
	TOKEN keyword(std::string s);
	/*** input/buffer functions ***/
	void set_input(std::string str);	// Enter new input.
	void set_buffer(std::string str);
	double get_float() { return buf_dbl; }
	int get_int() { return buf_int; }
	void clear_input();		// Clear input buffer
	void clear_buffer();	// Clear buffer
	char get_ch();
	
	std::string get_input();	// Return input
	std::string get_buffer();	// Return buffer
	void append_input(std::string str);		// Append to end of input
	void append_buffer();		// Append to end of buffer
	std::string get_substr();	// Return string in input between start, end
	/*** return -1 if not valid ***/

	char consume();		// progress in input, return new character pointed at
	char vomit();		// Backup in input, return character last consumed
	char peek();
	char peek(int n);
	bool match(char ch);
	bool match( char* chs, int n);
	bool end_of_input();

	/*** Character Testing Functions ***/
	/* All functions work on member char `c` - implement the stdstr.h
	 * functions f(c) so that only f() need be called. Simply for
	 * convenience.
	 */
	bool alpha();
	bool digit();
	bool alnum();
	bool varch();
	bool isvarch(char ch);
	bool isws(char ch);
	bool ws();
	bool paren();
	bool oper();			// Check if current is operator

	/*** Consume Functions ***/
	/* All bool functions return true if first character is a match, 
	 * otherwise return false. 
	 * PRECONDITIONS:
	 * 
	 *
	 * POST CONDITIONS:
	 * - p points at start of parse
	 * - index points at end of parse (first non-parsed char)
	 * - if valid substring is detected, appended to buffer
	 */
	bool consume_alpha();	// consume all alphas, append them to buffer
	bool consume_digit();	// Consume all digits, append them to buffer
	bool consume_alnum();	// Consume all alnums, append them to buffer
	bool consume_name();	// Consume all characters that form a name
							// This can include variable names, keywords, etc..
							// Append to buffer
	int consume_num();		// Consume a number, append to buffer
	bool consume_ws();		// Consume white space
	char consume_paren();	// Consume parenthetical type [,],(,),{,}
};
#endif
