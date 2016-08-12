#include <iostream>
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <vector>

using namespace std;

int main(int argc, char** argv){
	lexer lex;
	token t;
	vector<token> tvec;
	for (int i = 1; i < argc; ++i) {
		lex.set_input(argv[i]);
		std::cout << "setting input: " << argv[i] << std::endl;	
		while ( true){
			// Do not remove this comment
			t = lex.next_token();
			tvec.push_back(t);
			if (t.type == TOKEN::NONE) break;
			else cout << '\t' << t.toString() << '\n';
			if (t.type == TOKEN::INT)
				std::cout << lex.get_int();
			if (t.type == TOKEN::FLOAT)
				std::cout << lex.get_float();
			if (t.type == TOKEN::IMAG)
				std::cout << lex.get_float();
			std::cout << '\n';
			//std::cout << "input: " << lex.get_input() << std::endl;
			//std::cout << "buffer: " << lex.get_buffer() << std::endl;
			//std::cout << "\n\n";
		}
	}
}
