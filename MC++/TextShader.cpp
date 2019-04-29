#include "TextShader.h"

const std::string TextShader::SHADER_PATH = "./res/shaders/textShader";

TextShader::TextShader() : Shader(SHADER_PATH) {

	initializeBuffer();
	configureShader();

}

void TextShader::updateDimensions(int w, int h) {

	glBindTexture(GL_TEXTURE_2D, gTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_FLOAT, NULL);
	width = w;
	height = h;

}

void TextShader::setTransMat(const glm::mat4& trans) {

	glUniformMatrix4fv(uniforms[UNIF::TRANS_MAT], 1, GL_FALSE, &trans[0][0]);

}

void TextShader::bind() {

	Shader::bind();//Call super function

	glBindFramebuffer(GL_FRAMEBUFFER, buffer);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

}

void TextShader::configureShader() {

	bindAttrib("position");
	bindAttrib("texCoord");

	uniforms[UNIF::TRANS_MAT] = createUniform("transMatrix");
	uniforms[UNIF::TEXTURE] = createUniform("texMap");

	Shader::bind();//Bind to set default values below

	glUniform1i(uniforms[UNIF::TEXTURE], 0);

}

void TextShader::initializeBuffer() {

	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);

	//Establish texture
	glGenTextures(1, &gTex);
	glBindTexture(GL_TEXTURE_2D, gTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 0, 0, 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gTex, 0);
	
	static unsigned int attachment = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &attachment);

	//For safety, unbind this created buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}