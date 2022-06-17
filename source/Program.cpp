#include "Program.h"

Program::Program(GLFWwindow* in_window, int width, int height, inputData& input) : 
	input(input), window(in_window), window_width(width), window_height(height) {

	run = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.85f, 0.85f, 0.95f, 1.0f);

	level = std::shared_ptr<Level>(new Level(width, height, input));
}

void Program::Update(long time) {
	level->Update(time);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level->Draw();

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (input.keys["escape"]) {
		run = false;
	}
}