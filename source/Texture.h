#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <iostream>

#include "GL/glew.h"

#include "FileInput.h"

class Texture {
private:
	unsigned int texture;
	int width, height;
public:
	Texture(const std::string& path);

	void Bind(int i);
	void Unbind(int i);

	int GetWidth() const;
	int GetHeight() const;

	~Texture();
};

#endif