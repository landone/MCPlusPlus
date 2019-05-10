#include "Text.h"
#include "GameAssetLoader.h"

using namespace std;

Text::Text(string str) {

	shader = BasicShader::getGlobal();

	text = str;
	font_enum = FONT::ASCII;
	font = GameAssetLoader::getFont(font_enum);
	GLuint gltex;
	buf = shader->createBuffer();
	gltex = shader->createTex();
	tex.setIndex(gltex);
	createTexture();

}

void Text::setSize(float height) {

	height /= 2.0f; //Account for being 2 units large
	graphic.trans.SetScale(glm::vec3(height * text.length(), height, 1));

}

void Text::setString(std::string str) {

	text = str;
	createTexture();

}

void Text::setFont(FONT ft) {

	font_enum = ft;
	font = GameAssetLoader::getFont(font_enum);
	createTexture();

}

void Text::setColor(glm::vec3 col) {

	color = col;
	createTexture();

}

void Text::createTexture() {

	GLint prevBound = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevBound);

	BasicShader& shaderef = *shader;
	shaderef.setBuffer(buf);
	shaderef.setGLTex(tex.getIndex());
	int len = text.length();
	float width = font.getWidth() / 16 * len;
	float height = font.getHeight() / 16;
	tex.setWidth(width);
	tex.setHeight(height);
	/* Assume ascii 16*16 character map*/
	shaderef.updateDimensions(width, height);
	shaderef.setTint(color);
	font.bind();
	Mesh& mesh = *Graphic::getQuadMesh();
	Transform trans;
	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	trans.SetScale(glm::vec3((1.0f / len)* width / dims[2], 1.0f * height / dims[3], 1));
	for (int i = 0; i < len; i++) {

		trans.SetPos(glm::vec3((-1.0f + i * 2.0f / len+ 1) / dims[2] * width - 1,-1,0));
		shaderef.setTransMat(trans.GetMatrix());
		char c = text.at(i);
		glm::vec2 bottomLeft((c % 16) / 16.0f, (c / 16 + 1) / 16.0f);
		mesh.setQuadTextureCoord(bottomLeft, bottomLeft + glm::vec2(1/16.0f, -1/16.0f));
		mesh.draw();

	}

	mesh.setQuadTextureCoord(glm::vec2(0, 0), glm::vec2(1, 1));
	//tex = shaderef.getTex();

	glBindFramebuffer(GL_FRAMEBUFFER, prevBound);

	graphic.setTexture(tex);
	graphic.trans.SetPos(glm::vec3(-1, -1, 0));
	setSize(graphic.trans.GetScale().y);

}