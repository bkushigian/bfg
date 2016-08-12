/* expr.hpp
 * defines expression class and its subclasses
 * */
#include "token.hpp"
class expr : public statement; // Forward declaration
class expr{

};

class expr_numeric : public expr{

};
class expr_integral : public expr_numeric {

};
class expr_bool : public expr_integral {

};

class expr_int : public expr_integral {

};

class expr_char : public expr_integral {
	
};

class expr_complex : public expr_numeric {

};

class expr_float : public expr_numeric {

};

class expr_string : public expr {

};
