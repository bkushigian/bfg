#include "lexer.hpp"

lexer::lexer(){
	buffer = "";
	input = "";
	size = 0;
	index = 0;
	start = 0;
	end = 0;
}

void lexer::set_input(std::string str){
	input = str;
	buffer = "";
	size = input.length();
	index = 0;
	start = 0;
	end = 0;
}
void lexer::set_buffer(std::string str){
	buffer = str;
}
void lexer::clear_input(){
	input = "";
	size = 0;
	index = 0;
	start = 0; end = 0;
}

void lexer::clear_buffer(){
	buffer = "";
}
char lexer::get_ch(){
	if (index < 0 || index >= input.size()) return -1;
	return input[index];
}
std::string lexer::get_input(){
	return input;
}

std::string lexer::get_buffer(){
	return buffer;
}

void lexer::append_input(std::string str){
	input.append(str);
	size = input.length();
}

void lexer::append_buffer(){
	buffer.append(input.substr(p, index-p));
}

std::string lexer::get_substr(){
	if (start < 0 || end > size || start >= end) return "";
	return input.substr(start, end - start);
}

bool lexer::match(char ch) {
	return get_ch() == ch;
}

bool lexer::match(char* chs, int n){
	for (int i = 0; i < n; ++i)
		if (chs[i] == get_ch()) return true;
	return false;
}

/* Return next character in input. Increment index */
char lexer::consume(){
	if (index >= size) return -1;
	return input[index++];
}

/* Decrease index, return character in input. */
char lexer::vomit(){
	if (index == 0) return -1;
	return input[--index];
}

char lexer::peek(){
	if (index  >= size) return -1;
	return input[index+1];
}
char lexer::peek(int n){
	if (index + n >= size) return -1;
	return input[index + n];
}

bool lexer::end_of_input(){
	return (index >= size);
}

/*** Character Testing Functions ***/



bool lexer::alpha() {
	return isalpha(get_ch());
}
bool lexer::digit(){
	return isdigit(get_ch());
}
bool lexer::alnum(){
	return isalnum(get_ch());
}
bool lexer::varch(){
#if lexdebug
	std::cout << get_ch() << std::endl;
#endif
	return (alnum() || get_ch() == '_' || digit());
}
bool lexer::isvarch(char ch){
	return (isalnum(ch) || ch == '_');
}
bool lexer::isws(char ch){
	return (ch == '\t' || ch == ' ' || ch == '\n' || ch == '\r');
}
bool lexer::ws(){
	return isws(get_ch());
}
bool lexer::paren(){
	return (match('(') || match(')') || match('[') || match(']')
			|| match('{') || match('}'));
}
bool lexer::oper(){
	std::string s = "+-/=*.";
	for (int i = 0; i < s.size(); ++i) if (s[i] == get_ch()) return true;
	return false;
}
/*** Consume Functions ***/



bool lexer::consume_alpha(){
	if (end_of_input()) return false;
	if (!alpha()) return false;
	p = index;
	while (alpha() && index < size) consume();
	append_buffer();
	return true;
}
bool lexer::consume_digit(){
	if (end_of_input()) return false;
	if (!digit()) return false;
	p = index;
	while (digit() && index < size) consume();
	append_buffer();
	return true;
}
bool lexer::consume_alnum(){
	if (end_of_input()) return false;
	if (!alnum()) return false;
	p = index;
	while (alnum() && index < size)	consume();
	append_buffer();
	return true;
}
bool lexer::consume_name(){
	if (end_of_input()) return false;
	// Valid names start with character
	if (!alpha())	return false;
	p = index;
	while (varch() && index < size){
#if lexdebug
		std::cout << "consuming " << consume() << std::endl;
#else
		consume();
#endif
	}
	append_buffer();
	return true;
}

// Return 0 if not a number
// Return 1 if int
// Return 2 if double
// Return 3 if imaginary
int lexer::consume_num(){	
#if lexdebug
	std::cout << "consume_num()\n";
#endif
	if (end_of_input()) return false;
	p = index;
	int num_type = ( digit() ) ? 1 : 0;		// int : NaN
#if lexdebug
	std::cout << "\tnum_type = " << num_type << std::endl;
#endif
	consume_digit();
	if (match('.')){
#if lexdebug
		std::cout << "\tis a decimal\n";
#endif
		consume();				// Consume '.'
		if (digit()){
			num_type = 2;		// float
			consume_digit();
			append_buffer();
			buf_dbl = atof(buffer.c_str());
		}
		else if (num_type == 1)
			num_type = 2;
		else if (num_type == 0) 	// Check if just '.'
			vomit();				// We consumed '.', give it back
	}
	if (match('i') && num_type){	// Update so that 10i10, 10ia, etc is
									// not valid
		consume();
		num_type = 3;		// Check if imaginary
	}
#if lexdebug
	std::cout << "\tat return, num_type = " << num_type << std::endl;
#endif
	return num_type;
}

bool lexer::consume_ws(){
	if (end_of_input()) return false;
	if (!ws()) return false;
	while (ws()) consume();
	return true;
}

char lexer::consume_paren(){
	if (end_of_input()) return 0;
	if (!paren()) return 0;
	return consume();
}

token lexer::next_token(){
	// FOR DEBUG
#if lexdebug
	std::cout << "Calling next_token()\n";
	std::cout << "peek() = " << peek() << std::endl;
#endif
	char ch;			// For temp storage
	TOKEN T;
	if (end_of_input()) 
		return token(TOKEN::NONE, "none");
	consume_ws();
	start = index;		// Store start index
	end = start;		// ...and the end index
	/****************************************************
	 * First, check if is number
	 ****************************************************/
	
	if (digit() || match('.')){
		int numType = consume_num();	// Doesn't consume if not num
#if lexdebug
		std::cout << "we consumed a number\n";
#endif
		switch (numType){	// int

			case 1: 
				buf_int = std::atoi(input.substr(start, index - start).c_str());
				return token(TOKEN::INT, input.substr(start, index - start));
			case 2:
				buf_dbl = std::atof(input.substr(start, index - start).c_str());
				return token(TOKEN::FLOAT, input.substr(start, index - start));
			case 3:

				buf_dbl = std::atof(input.substr(start, index - start - 1).c_str());
				return token(TOKEN::IMAG, input.substr(start, index-start));
		}
	}
	
	/******************************************************
	 * Check if is alpha
	 *****************************************************/
	if (consume_name()) {
#if lexdebug
		std::cout << "consuming alpha\n";
#endif
		end = index;
		if ((T = keyword(get_substr())) != TOKEN::NONE){
			return token(T, get_substr());
		}
		return token(TOKEN::VAR, get_substr());
	}
	/*****************************************************
	 * Check Paren
	 * **************************************************/
	if (paren()){
#if lexdebug
		std::cout << "consuming some sort of parenthase... MMMMM, tasty\n";
#endif
		ch = consume_paren();
#if lexdebug
		std::cout << "parenthese looks like this: " << ch << ", " << (int) ch << std::endl;
#endif
		switch (ch) {
			case '{':
				return token(TOKEN::LBRACE, "{");
			case '}':
				return token(TOKEN::RBRACE, "}");
			case '[':
				return token(TOKEN::LBRACK, "[");
			case ']':
				return token(TOKEN::RBRACK, "]");
			case '(':
				return token(TOKEN::LPAREN, "(");
			case ')':
				return token(TOKEN::RPAREN, ")");

		}
	}
	/********************************************************
	 * Check if operator
	 * *****************************************************/
	if (oper())	{
		ch = consume();
		switch (ch ){
			case '+':
				if (peek() == '+') {
					consume();
					return token(TOKEN::INCR, "++");
				}
				if (peek() == '='){
					consume();
					return token(TOKEN::PLUSEQ, "+=");
				}
				return token(TOKEN::ADD, "+");
			case '-':
				if (peek() == '-'){
					consume();
					return token(TOKEN::DECR, "--");
				}
				if (peek() == '=') {
					consume();
					return token(TOKEN::MINUSEQ, "-=");
				}
				return token(TOKEN::SUBTRACT, "-");
			case '*':
				if (peek() == '=') {
					consume();
					return token(TOKEN::MULTEQ, "*=");
				}
				if (peek() == '*') {
					consume();
					return token(TOKEN::POWER, "**");
				}
				return token(TOKEN::MULTIPLY, "*");
			case '/':
				if (peek() == '=') {
					consume();
					return token(TOKEN::DIVEQ, "/=");
				}
				return token(TOKEN::DIVIDE, "/");
			case '.':
				if (peek() == '.') {
					consume(); 
					return token(TOKEN::ELIPSES, "..");
				}
				return token(TOKEN::DOT, ".");
			case '=':
				if (peek() == '='){
					consume();
					return token(TOKEN::EQUALITY, "==");
				}
				return token(TOKEN::EQUAL, "=");
		}
	}
	if (get_ch() == ';'){
		consume();
		return token(TOKEN::SEMICOLON, ";");
	}
	if (match('"')){
		consume();
		return token(TOKEN::QUOTE, "\"");
	}
	if (match('\'')){
		consume();
		return token(TOKEN::APOSTROPHE, "'");
	}

#if lexdebug
	std::cout << "Returning NONE token\n";
#endif
	return token(TOKEN::NONE, "none");

}


TOKEN lexer::keyword(std::string s){
	if (s.compare("let") == 0)
		return TOKEN::LET;
	if (s.compare("if") == 0)
		return TOKEN::IF;
	if (s.compare("for") == 0)
		return TOKEN::FOR;
	if (s.compare("while") == 0)
		return TOKEN::WHILE;
	if (s.compare("create") == 0)
		return TOKEN::CREATE;
	if (s.compare("remove") == 0)
		return TOKEN::REMOVE;
	if (s.compare("info") == 0)
		return TOKEN::INFO;
	if (s.compare("ls") == 0)
		return TOKEN::LS;
	if (s.compare("view") == 0)
		return TOKEN::VIEW;
	if (s.compare("init") == 0)
		return TOKEN::INIT;
	if (s.compare("load") == 0)
		return TOKEN::LOAD;
	if (s.compare("save") == 0)
		return TOKEN::SAVE;
	if (s.compare("mandelbrot") == 0)
		return TOKEN::MANDELBROT;
	if (s.compare("julia") == 0)
		return TOKEN::JULIA;
	return TOKEN::NONE;
}
