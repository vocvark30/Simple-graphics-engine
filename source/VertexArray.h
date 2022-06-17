#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <vector>

#include <GL/glew.h>

class VertexArray {
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;

	size_t indicesCount;
public:
	VertexArray(std::vector<float> vertices, std::vector<unsigned int> indices,
		const std::vector<int>& floatsInVertex);
	void Draw() const;
	~VertexArray();
};

#endif