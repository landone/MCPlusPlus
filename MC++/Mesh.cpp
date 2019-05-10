#include "Mesh.h"

Mesh& Mesh::Init(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = vertices;
	this->indices = indices;
	indexSize = indices.size();
	setupMesh();
	return *this;
}

void Mesh::Init(GLuint vao, size_t indexSize) {
	this->VAO = vao;
	this->indexSize = indexSize;
}

void Mesh::setQuadTextureCoord(glm::vec2 bottomLeft, glm::vec2 topRight) {

	if (vertices.size() != 4) {//Must be quad
		return;
	}

	vertices[0].texCoord = glm::vec2(bottomLeft.x, topRight.y);
	vertices[1].texCoord = topRight;
	vertices[2].texCoord = glm::vec2(topRight.x, bottomLeft.y);
	vertices[3].texCoord = bottomLeft;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
	glBindVertexArray(0);

}

void Mesh::setTextureScale(glm::vec2 scale) {
	textureScale.x = scale.x / textureScale.x;
	textureScale.y = scale.y / textureScale.y;
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].texCoord.x *= textureScale.x;
		vertices[i].texCoord.y *= textureScale.y;
	}
	textureScale = scale;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
	glBindVertexArray(0);
}

void Mesh::setupMesh() {
	if (VAO == NULL) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glBindVertexArray(0);
}

void Mesh::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
}