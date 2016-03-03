#include "interpreter.hpp"

interpreter::interpreter(){

}

interpreter::interpreter(fManager* fm){
	FM = fm;
}

interpreter::interpreter(fManager* fm, winManager* wm){
	FM = fm;
	WM = wm;
}


int interpreter::parse(std::string c){
	return 0;
}
