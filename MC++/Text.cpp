#include "Text.h"
#include "GameTextureLoader.h"

using namespace std;

Text::Text(string str) {

	text = str;
	font = GameTextureLoader::getFont();
	createTexture();
	graphic.setTexture(tex);
	graphic.trans.SetPos(glm::vec3(-1, -1, 0));
	glm::vec3 scale(font.getWidth() * str.length() * 9, font.getHeight() * 16, 0);
	scale = glm::normalize(scale);
	scale.z = 1;
	graphic.trans.SetScale(scale);

}

void Text::createTexture() {

	GLint prevBound = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevBound);

	shader.bind();
	int len = text.length();
	float width = font.getWidth() / 16 * len;
	float height = font.getHeight() / 16;
	/* Assume ascii 16*16 character map*/
	shader.updateDimensions(width, height);
	font.bind();
	Mesh& mesh = *Graphic::getQuadMesh();
	Transform trans;
	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	trans.SetScale(glm::vec3((1.0f / len)* width / dims[2], height / dims[3], 1));
	for (int i = 0; i < len; i++) {

		trans.SetPos(glm::vec3((-1.0f + i * 2.0f / len+ 1) / dims[2] * width - 1,-1,0));
		shader.setTransMat(trans.GetMatrix());
		char c = text.at(i);
		glm::vec2 bottomLeft((c % 16) / 16.0f, (c / 16 + 1) / 16.0f);
		mesh.setQuadTextureCoord(bottomLeft, bottomLeft + glm::vec2(1/16.0f, -1/16.0f));
		mesh.draw();

	}

	mesh.setQuadTextureCoord(glm::vec2(0, 0), glm::vec2(1, 1));
	tex = shader.getTex();

	glBindFramebuffer(GL_FRAMEBUFFER, prevBound);

}