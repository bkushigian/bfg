#ifndef interpreter_hpp
#define interpreter_hpp


#include <string>
#include <sstream>
#include <vector>
#include "../Fractals/fManager.hpp"
#include "../Fractals/julia.hpp"
#include "../Globals/globals.hpp"

#include <map>

class interpreter : public object {
private:
	fManager* FM;
	winManager* WM;
	std::string* history;
public:
	interpreter();
	interpreter(fManager* fm);
	interpreter(fManager* fm, winManager* wm);
	void parse(std::string c);
};

class tokenizer{

};
#endif
