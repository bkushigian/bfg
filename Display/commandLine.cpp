#include "commandLine.hpp"

commandLine::commandLine(){
	buffer = "";
	historySize = 0;
	pos = 0;
	size = 0;
	prompt = "$ ";
}

void commandLine::insert(char c){		// insert char into string
	// @ToDo: check for non-writable characters
	buffer.insert(pos, 1, c);
	++size;
	++pos;
}


void commandLine::remove(){			// From backspace call
	if (pos > 0){
		buffer.erase(pos-1, 1);
		--size;
		--pos;
	}
}

std::string commandLine::truncate(){
	std::string s = buffer;
	buffer = "";
	size = 0;
	pos = 0;
	return s;
}

int commandLine::execute(){
	// @ToDo - make execute work lolz
	clHistory.push_back(buffer);
	++historySize;
	truncate();
	return 0;
}

std::string commandLine::toString() { 
	return prompt + buffer; 
}

std::string commandLine::getHistory(int n){
	if (n >= 0 && n < historySize)
		return clHistory[n];
	else if ( -n <= historySize)
		return clHistory[size + n];
}
//movement
unsigned int commandLine::left(){
	if (pos > 0){
		--pos;
	}
	return pos;
}


unsigned int commandLine::right(){
	if (pos + 1 < size ) ++pos;
	return pos;
}

unsigned int commandLine::up(){
	return 0;
}
unsigned int commandLine::down(){
	return 0;
}