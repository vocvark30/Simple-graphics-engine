#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <map>
#include <string>

/*
	inputData:
		struct for save and processing input between classes
*/

struct inputData {
	std::map<std::string, bool> keys;
	double mouse_x = 0.0, mouse_y = 0.0;

	inputData() {
		keys["w"] = false;
		keys["a"] = false;
		keys["s"] = false;
		keys["d"] = false;
		keys["space"] = false;
		keys["escape"] = false;
		keys["right"] = false;
		keys["left"] = false;
	}
};

#endif