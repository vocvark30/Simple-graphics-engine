#define GLEW_STATIC

#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Program.h"

inputData input;

void KeyCallback(GLFWwindow* w, int key, int scancode, int action, int modifications) {
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			input.keys["d"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["d"] = false;
		}
	} else if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			input.keys["w"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["w"] = false;
		}
	} else if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			input.keys["a"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["a"] = false;
		}
	} else if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			input.keys["s"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["s"] = false;
		}
	} else if (key == GLFW_KEY_ESCAPE) {
		if (action == GLFW_PRESS) {
			input.keys["escape"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["escape"] = false;
		}
	} else if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			input.keys["space"] = true;
		} else if (action == GLFW_RELEASE) {
			input.keys["space"] = false;
		}
	}
}

void MouseCallback(GLFWwindow* w, double x, double y) {
	input.mouse_x = x;
	input.mouse_y = y;
}

void MouseButtonCallback(GLFWwindow* w, int button, int action, int modifications) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			input.keys["left"] = true;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			input.keys["right"] = true;
		}
	}

	if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			input.keys["left"] = false;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			input.keys["right"] = false;
		}
	}
}

int main() {
	{
		const int width = 1600;
		const int height = 900;
		const std::string title = "Graphics Engine";

		if (!glfwInit()) {
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);

		glfwGetCursorPos(window, &input.mouse_x, &input.mouse_y);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!window) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK) {
			return -1;
		}


		glfwSwapInterval(1);
		{
			auto time1 = std::chrono::system_clock::now();

			Program program(window, width, height, input);

			auto time2 = std::chrono::system_clock::now();

			std::cout << "start time: " 
				<< std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count()
				<< std::endl;


			long frames = 0;
			long time = 0;

			time1 = std::chrono::system_clock::now();
			auto frameTimePoint = std::chrono::system_clock::now();

			while (program.run) {
				frameTimePoint = std::chrono::system_clock::now();
				program.Update(time);
				frames++;
				time = std::chrono::duration_cast<std::chrono::microseconds>
					(std::chrono::system_clock::now() - frameTimePoint).count();
			}

			float framesPerSecond = frames / 
					(std::chrono::duration_cast<std::chrono::microseconds>
					(std::chrono::system_clock::now() - time1).count() / 1000000.0f);

			std::cout << "average fps = " << framesPerSecond << std::endl;
		}
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	return 0;
} 