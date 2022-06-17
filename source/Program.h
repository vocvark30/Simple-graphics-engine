#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Level.h"
#include "InputData.h"

/*
	Program:
		Clear OpenGL buffers, draws Levels, setups OpenGL environment
		layer between main() and level processing
*/

class Program {
private:
	GLFWwindow* window;
	int window_width, window_height;

	inputData& input;

	std::shared_ptr<Level> level;
public:
	bool run;

	Program(GLFWwindow* in_window, int width, int height, inputData& input);

	// time in microseconds
	void Update(long time);
};

#endif