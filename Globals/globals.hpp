/* globals.hpp - defines global types and enums to be used throughout the
 * program. 
 */

#ifndef FRACTAL_GLOBALS_HPP
#define FRACTAL_GLOBALS_HPP

#include <SFML/Config.hpp>
#include "../math/complex.hpp"
// Typedefs
typedef 	sf::Uint8 		Uint8;
typedef 	sf::Uint16 		Uint16;

// Enums

// Fractal Type (Not currently used, but included in fractal.hpp
enum FRACTAL_TYPE { 
	FT_NONE				= 0, 
	FT_JULIA			= 1, 
	FT_MANDEL			= 2, 
	FT_NEWTON			= 3, 
	FT_SIERP			= 4 
};
// Render Mode - replace with DSP_MODE
// enum RNDR_MODE {RNDR_NONE, RNDR_TRIANGLES, RNDR_PIXARRAY};

// Dispaly Mode - how is this to be displayed
enum DSP_MODE {
	DSP_NONE 			= 0,
	DSP_PIXARRAY 		= 1,
	DSP_TRIANGLES 		= 2,
	DSP_IFS				= 4,
	DSP_MRCM			= 8,
	DSP_TEXT			= 16
};

// Event Handling Mode - how do we handle keyboard/mouse etc?
enum EVENT_HANDLE_MODE {
	HNDL_NONE			= 0, 
	HNDL_NORMAL 		= 1, 
	HNDL_CMND			= 2
};
#endif

