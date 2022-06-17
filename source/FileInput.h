#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "stb_image/stb_image.h"

#include "Vector3.h"

/*
	FileInput:
		static class for reading files - texts, models, textures.
*/


// struct to return data from readObejct(...)
struct geometryStructure {
	std::vector<Vector3> vertices;				// Unpacked data for geometry objects,
	std::vector<unsigned int> indices;

	std::vector<float> drawingVertices;			// ... and for vertex array
	std::vector<unsigned int> drawingIndices;
};

class FileInput {
private:
	FileInput() = delete;

	static std::vector<std::string> splitString(const std::string& in, const std::string& s);

public:
	static std::string getString(const std::string& path);

	static geometryStructure readObject(std::string path);

	static unsigned char* loadImage(const std::string& path, int* width, int* height);
	static void deleteImage(void* data);
};


#endif 
