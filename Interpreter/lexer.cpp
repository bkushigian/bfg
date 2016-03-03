#include "lexer.hpp"

lexer::lexer(){
	buffer = "";
	input = 0;
	size = 0;
	index = 0;
}

void lexer::set_input(std::string str){
	buffer = str;
	size = buffer.length();
	parsing = true;
	index = 0;
}
void lexer::clear_buffer(){
	buffer = "";
}

std::string lexer::get_buffer(){
	return buffer;
}

void lexer::append_buffer(){
	buffer.append(input.sbustr(p, index-p));
}
bool lexer::match(char ch) {
	return c == ch;
}

char lexer::consume(){
	if (index >= size) return -1;
	return input[++index];
}
char lexer::vomit(){
	if (index == 0) return -1;
	return input[index--];
}
char lexer::peek(){
	if (index >= size) return -1;
	return input[index + 1];
}
char lexer::peek(int n){
	if (index + n >= size) return -1;
	return input[index + n];
}

/*** Consume Functions ***/

bool lexer::consume_alpha(){
	if (!isalpha()) return false;
	p = index;
	while (isalpha()) consume();
	append_buffer();
	return true;
}
bool lexer::consume_digit(){
	if (!isdigit()) return false;
	p = index;
	while (isdigit()) consume();
	append_buffer();
	return true;
}
bool lexer::consume_alphadigit(){
	if (!isalphadigit()) return false;
	p = index;
	while (isalphadigit())	consume();
	append_buffer();
	return true;
}
bool lexer::consume_name(){
	if (!isvarch())	return false;
	p = index;
	while (isvarch()) consume();
	append_buffer();
	return true;
}

// Return 0 if not a number
// Return 1 if int
// Return 2 if double
int lexer::consume_number(){	
	p = index;
	int num_type = ( isdigit(peek()) ) ? 1 : 0;
	while ( isdigit()) consume();
	if (match('.')){
		consume();
		if (isdigit(peek())){
			num_type = 2;
		
			while (isdigit()) consume();
			append_buffer();
			buf_dbl = atof(buffer);
		}
	}
	return num_type;
	
}
bool lexer::consume_ws(){
	if (!isws()) return false;
	while (isws()) consume();
	return true;
}

token lexer::next token(){
	consume_ws();
	int i0 = index;		// Store start index
	int end = i0;
	// First, check if is number
	int numType = consume_number();
	if (numType){
		if (numType == 1){	// int
			return token(TOKEN::INT, buffer.substr(i0, index - i0);
		}
		return token(TOKEN::DOUBLE, buffer,substr(i0, index - i0);
	}
	
	
	// If not, check if is alpha
	while (isalpha(c)) consume();	// Cycle through alpha, check if keyword
	end = index;

	while (isvarch(c)) consume();	
}


