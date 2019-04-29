#pragma once

#include "Shader.h"
#include "Texture.h"

class TextShader : private Shader{
public:

	TextShader();

	void bind() override;
	void updateDimensions(int width, int height);
	void setTransMat(const glm::mat4& trans);

	Texture getTex() { return Texture(gTex, width, height); }

private:
	GLuint buffer = 0;
	GLuint gTex = 0;

	int width = 0;
	int height = 0;

	void initializeBuffer();
	void configureShader();

	enum UNIF {
		TRANS_MAT,
		TEXTURE,
		TOTAL
	};

	GLuint uniforms[UNIF::TOTAL];

	static const std::string SHADER_PATH;

};