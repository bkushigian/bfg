#ifndef bfg_object_hpp
#define bfg_object_hpp

#include "../Globals/globals.hpp"
#include <string>


class object {
protected:
	DSP_MODE displayMode;
	OBJ_TYPE objectType;
	std::string name;
public:
	object(){
		displayMode = DSP_NONE;
		objectType = OBJ_OBJECT;
		name = "Generic Object";
	}
	virtual void draw() {}
	virtual std::string getName() {return name; }
	virtual int handleEvent(char event) { return 0; }
	virtual int rClick(int x, int y) { return 0; }
	virtual int lClick(int x, int y) { return 0; }
	virtual DSP_MODE getDisplayMode(){ return displayMode; }
	virtual OBJ_TYPE getObjectType() { return objectType; }
	virtual void init() {};
};



#endif
