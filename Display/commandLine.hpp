#ifndef commandline_hpp
#define commandline_hpp

#include <string>
#include <vector>
class commandLine{
private:
	std::string buffer;			// Current command being entered;
	unsigned int pos;			// Current position
	unsigned int size;			// Size of buffer
	std::string prompt;
	std::vector<std::string> clHistory;
	unsigned int historySize;
public:
	commandLine();

	void insert(char c);
	void remove();
	std::string getBuffer(){ return buffer; }
	std::string toString();
	std::string truncate();
	int execute();
	unsigned int getPos(){ return pos; }
	unsigned int getSize(){ return size; }
	std::string getHistory(int n);
	unsigned int getHistorySize() { return historySize; }
	//movement
	unsigned int left();
	unsigned int right();
	unsigned int up();
	unsigned int down();
	

};
#endif
