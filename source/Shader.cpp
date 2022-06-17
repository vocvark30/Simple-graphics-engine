#include "Shader.h"

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, 
	const std::string& path) : texture(path) {

	program = glCreateProgram();

	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << "Shader compilation failed!" << std::endl;
		std::cout << "Shader : " << source << std::endl;
		return 0;
	}

	return id;
}

int Shader::GetUniformLocation(const std::string& name) {
	return glGetUniformLocation(GetProgram(), name.c_str());
}

unsigned int Shader::GetProgram() const {
	return program;
}

void Shader::SetMatrix(unsigned int location, const glm::mat4& matrix) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetInt(unsigned int location, int i) {
	glUniform1i(location, i);
}

void Shader::SetFloat(unsigned int location, float f) {
	glUniform1f(location, f);
}

void Shader::SetVec3(unsigned int location, const Vector3& v) {
	glUniform3f(location, v.x, v.y, v.z);
}

void Shader::Bind() {
	glUseProgram(program);
	texture.Bind(0);
}

void Shader::Unbind() {
	texture.Unbind(0);
	glUseProgram(0);
}

Shader::~Shader() {
	glDeleteProgram(program);
}