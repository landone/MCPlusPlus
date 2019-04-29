#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh {
public:

	~Mesh();

	Mesh() {}
	Mesh(std::vector<Vertex> verts, std::vector<GLuint> indices) {
		Init(verts, indices);
	}

	Mesh& Init(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void Init(GLuint VAO, size_t indexSize);

	void draw();

	void setTextureScale(glm::vec2 scale);

	void setQuadTextureCoord(glm::vec2 bottomLeft, glm::vec2 topRight);

	GLuint getVAO() { return VAO; }
	size_t getIndSize() { return indexSize; }

private:
	GLuint VAO = NULL, VBO = NULL, EBO = NULL;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices; GLuint indexSize = 0;
	void setupMesh();

	glm::vec2 textureScale = glm::vec2(1, 1);
};