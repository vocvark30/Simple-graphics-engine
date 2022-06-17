#include "FileInput.h"

struct Vertex {
	Vector3 v, normal;
	float texture_x, texture_y;


	Vertex();
	bool operator==(const Vertex& v) const;
};

struct index {
	unsigned int vertex, texture, normal;
	index() : vertex(0), texture(0), normal(0) { }
};

Vertex::Vertex() : v(), normal(), texture_x(0.0f), texture_y(0.0f) {}

bool Vertex::operator==(const Vertex& in_vertex) const {
	return
		(v.x == in_vertex.v.x) && (v.y == in_vertex.v.y) && (v.z == in_vertex.v.z) &&
		(texture_x == in_vertex.texture_x) && (texture_y == in_vertex.texture_y) &&
		(normal.x == in_vertex.normal.x) && (normal.y == in_vertex.normal.y) && (normal.z == in_vertex.normal.z);
}


std::string FileInput::getString(const std::string& path) {
	std::string source;
	std::ifstream sourceFile(path);
	std::string line;

	while (getline(sourceFile, line)) {
		source += line + '\n';
	}

	sourceFile.close();
	return source;
}

std::vector<std::string> FileInput::splitString(const std::string& in, const std::string& s) {
	std::vector<std::string> result;

	size_t begin = 0;
	size_t it = in.find(s, 0);

	std::string t;

	while (it != -1) {
		t = in.substr(begin, it - begin);
		result.push_back(t);
		begin = it + 1;
		it = in.find(s, begin);
	}

	t = in.substr(begin, in.length() - begin);
	if (t != "") {
		result.push_back(t);
	}

	return result;
}

geometryStructure FileInput::readObject(std::string path) {	
	geometryStructure geometry;

	std::vector<Vector3> textureVertices;
	std::vector<Vector3> normals;
	std::vector<index> indices;

	std::vector<Vertex> drawingVertices;

	std::vector<std::string> lines = splitString(FileInput::getString(path), "\n");
	std::vector<std::string> words;

	for (int i = 0; i < lines.size(); i++) {
		words = splitString(lines[i], " ");

		if ((words.size() >= 4) && (words[0] == "v")) {
			Vector3 v;
			v.x = std::stof(words[1]);
			v.y = std::stof(words[2]);
			v.z = std::stof(words[3]);

			geometry.vertices.push_back(v);
		}

		if ((words.size() >= 3) && (words[0] == "vt")) {
			Vector3 v;
			v.x = std::stof(words[1]);
			v.y = std::stof(words[2]);
			v.z = 0.0f;

			textureVertices.push_back(v);
		}

		if ((words.size() >= 4) && (words[0] == "vn")) {
			Vector3 v;
			v.x = std::stof(words[1]);
			v.y = std::stof(words[2]);
			v.z = std::stof(words[3]);

			normals.push_back(v);
		}

		if ((words.size() >= 4) && (words[0] == "f")) {
			std::vector<std::string> s = splitString(words[1], "/");

			bool vt = (s.size() >= 2) && (s[1] != "");
			bool vn = (s.size() >= 3) && (s[2] != "");

			for (int j = 1; j <= 3; j++) {
				index a;
				s = splitString(words[j], "/");

				a.vertex = std::stoul(s[0]) - 1;

				if (vt) {
					a.texture = std::stoul(s[1]) - 1;
				}

				if (vn) {
					a.normal = std::stoul(s[2]) - 1;
				}

				indices.push_back(a);
			}
		}
	}

	for (int i = 0; i < indices.size(); i++) {
		geometry.indices.push_back(indices[i].vertex);

		Vertex v;
		v.v = geometry.vertices[indices[i].vertex];
		v.texture_x = textureVertices[indices[i].texture].x;
		v.texture_y = textureVertices[indices[i].texture].y;
		v.normal = normals[indices[i].normal];

		int indexOfVertex = -1;
		for (int j = 0; j < drawingVertices.size(); j++) {
			if (drawingVertices[j] == v) {
				indexOfVertex = j;
				break;
			}
		}

		if (indexOfVertex == -1) {
			drawingVertices.push_back(v);
			indexOfVertex = drawingVertices.size() - 1;
		}

		geometry.drawingIndices.push_back(indexOfVertex);
	}

	for (int i = 0; i < drawingVertices.size(); i++) {
		geometry.drawingVertices.push_back(drawingVertices[i].v.x);
		geometry.drawingVertices.push_back(drawingVertices[i].v.y);
		geometry.drawingVertices.push_back(drawingVertices[i].v.z);
		
		geometry.drawingVertices.push_back(drawingVertices[i].texture_x);
		geometry.drawingVertices.push_back(drawingVertices[i].texture_y);
		
		geometry.drawingVertices.push_back(drawingVertices[i].normal.x);
		geometry.drawingVertices.push_back(drawingVertices[i].normal.y);
		geometry.drawingVertices.push_back(drawingVertices[i].normal.z);
	}

	return geometry;
}

unsigned char* FileInput::loadImage(const std::string& path, int* width, int* height) {
	stbi_set_flip_vertically_on_load(1);

	int channels;
	unsigned char* data = stbi_load(path.c_str(), width, height, &channels, STBI_rgb_alpha);

	return data;
}

void FileInput::deleteImage(void* data) {
	stbi_image_free(data);
}