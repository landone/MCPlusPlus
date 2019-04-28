#include "Graphic.h"
#include <iostream>

static std::vector<Vertex> face = { Vertex{ glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec2(0,1) },
Vertex{ glm::vec3(2, 0, 0), glm::vec3(0, 0, 1), glm::vec2(1,1) },
Vertex{ glm::vec3(2, 2, 0), glm::vec3(0, 0, 1), glm::vec2(1,0) },
Vertex{ glm::vec3(0, 2, 0), glm::vec3(0, 0, 1), glm::vec2(0,0) }
};

static std::vector<GLuint> indices = { 0, 1, 2,
2, 3, 0 };

Graphic::Graphic(Texture& tex) {

	mesh.Init(face, indices);
	this->tex = tex;
	trans.SetScale(glm::vec3(0.04, 0.04, 1.0));
	trans.SetPos(glm::vec3(-0.04, -0.04, 0));
}

void Graphic::setTexture(Texture& tex) {
	this->tex = tex;
}

void Graphic::onDrawGUI(GBuffer& gBuffer) {
	
	gBuffer.setTransMat(trans.GetMatrix());
	gBuffer.setRotMat(trans.GetRotMatrix());
	tex.bind();
	mesh.draw();

}