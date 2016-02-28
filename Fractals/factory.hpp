#ifndef factory_hpp
#define factory_hpp
#include "../Fractals/object.hpp"
#include "../Fractals/fractal.hpp"
#include "../Fractals/mandelbrot.hpp"
#include "../Fractals/julia.hpp"
#include "../Globals/globals.hpp"
#include <complex>
#include <string>
#include <unordered_map>

// For valuePair
enum VP_TYPE { UI8, UI16, UI32, UI64, DBL, FLT, CMPLX, STRNG };


// Factory creates an object
class factory{
private:
public:
	virtual object* create(){}
	virtual int update(std::string key, void* val){}
};


class valuePair{
public:
	valuePair(std::string s, Uint8 v){
		type = UI8;
		name = s;
		ui8 = v;
	}
	valuePair(std::string s, Uint16 v){
		type = UI16;
		name = s;
		ui16 = v;
	}
	valuePair(std::string s, Uint32 v){
		type = UI32;
		name = s;
		ui32 = v;
	}
	valuePair(std::string s, Uint64 v){
		type = UI64;
		name = s;
		ui64 = v;
	}
	valuePair(std::string s, double v){
		type = DBL;
		name = s;
		d = v;
	}
	valuePair(std::string s, cmplx v){
		type = CMPLX;
		name = s;
		cmp = v;
	}
	valuePair(std::string s, std::string v){
		type = STRNG;
		name = s;
		s = v;
	}
	
	Uint8  getUI8(){return ui8; }
	Uint16 getUI16(){return ui16; }
	Uint32 getUI32(){return ui32; }
	Uint64 getUI64(){return ui64; }
	double getDouble(){return d; }
	float getFloat(){return f; }
	cmplx getComplex(){return cmp; }
	std::string getString(){return s; }

	VP_TYPE type;
	std::string name;
private:
	// Anonymous Union
	union {
		Uint8  ui8;
		Uint16 ui16;
		Uint32 ui32;
		Uint64 ui64;
		double d;
		float  f;
		cmplx  cmp;
		std::string s;
		

	};
};
#endif
