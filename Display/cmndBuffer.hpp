#ifndef CMND_BUFFER_HPP
#define CMND_BUFFER_HPP

#include <string>
#include <iostream>
#include <sstream>
class cmndBuffer{
private:
	string cmnd;
	std::stringstream ss;
public:
	cmndBuffer(){ ss.str(std::string()); }
	void addCh(char c) {
		switch (c){
			case (char)0x1B:					// Escape
		 		ss.str(std::string());	break;	
			case (char)0xD:						// Return
				cmnd = ss.str(); break;
			case (char)0x8:						// Backspace
				cmnd = ss.str();
				cmnd.erase(cmnd.end());
				ss.str(cmnd);
				cmnd = "";
				break;
			default:
				ss << c;
		}
	}
};

#endif
