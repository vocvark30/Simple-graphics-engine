#include "VertexArray.h"

VertexArray::VertexArray(std::vector<float> vertices, 
	std::vector<unsigned int> indices, const std::vector<int>& floatsInVertex) {

	int floatsInVertexCount = 0;
	for (auto& v : floatsInVertex) {
		floatsInVertexCount += v;
	}

	const void* vertexData = vertices.data();
	const void* indexData = indices.data();

	int vertexSize = floatsInVertexCount * sizeof(float);

	this->indicesCount = indices.size();
	size_t verticesCount = vertices.size() / floatsInVertexCount;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * vertexSize, vertexData, GL_STATIC_DRAW);


	int floatsCount = 0;
	for (unsigned int i = 0; i < floatsInVertex.size(); i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, floatsInVertex[i], GL_FLOAT, GL_FALSE,
			vertexSize, (const void*)(floatsCount * sizeof(float)));
		//position of attribute, how many floats represents it, 
		//type, normalized, size in bytes to next vertex, offset
		floatsCount += floatsInVertex[i];
	}

	// index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::Draw() const {
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArrayObject);
}
