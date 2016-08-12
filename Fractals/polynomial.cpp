#include "polynomial.hpp"

poly::poly(std::string s, char v) {
	var = v;
	coef = parseString(s, v);
	
}

std::vector<cmplx> parseString(std::string s, char v){
	int i = 0;
	int j = 0;
	while (j < s.length()){
		i = j;
		if (s[j] == v){
			if (j + 1 < s.length()){
				
			}
		}
	}
}
