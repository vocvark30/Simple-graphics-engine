#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include "glm/glm.hpp"

#include "Texture.h"
#include "Vector3.h"

/*
	Shader:
		Compiles shader program from sources, contains and manages textures
		Should be binded before using, and unbinded after using
*/

class Shader {
private:
	unsigned int program;
	unsigned int compileShader(unsigned int type, const std::string& source);

	Texture texture;
public:
	Shader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& path);

	int GetUniformLocation(const std::string& name);

	unsigned int GetProgram() const;

	void SetMatrix(unsigned int location, const glm::mat4& matrix);
	void SetInt(unsigned int location, int i);
	void SetFloat(unsigned int location, float f);
	void SetVec3(unsigned int location, const Vector3& v);

	void Bind();
	void Unbind();

	~Shader();
};

#endif