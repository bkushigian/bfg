#include "parser.hpp"


parser::parser(){
	index = 0;
}
void parser::set_input(std::string s){
	lex.set_input(s);
	token t;
	while ((t = lex.next_token()).type != TOKEN::NONE)
		vec_t.push_back(t);
}
