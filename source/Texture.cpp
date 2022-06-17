#include "Texture.h"

Texture::Texture(const std::string& path) {
	texture = 0;
	width = 0;
	height = 0;

	unsigned char* textureData = FileInput::loadImage(path, &width, &height);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	glBindTexture(GL_TEXTURE_2D, 0);

	FileInput::deleteImage(textureData);
}

void Texture::Bind(int i) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, texture);
}
void Texture::Unbind(int i) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const {
	return width;
}

int Texture::GetHeight() const {
	return height;
}

Texture::~Texture() {
	glDeleteTextures(1, &texture);
}