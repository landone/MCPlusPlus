#pragma once

#include "LightShader.h"

class GBuffer : private Shader{
public:

	GBuffer();

	void bind() override;
	void updateDimensions(int width, int height);

	void setTint(const glm::vec3& color);
	void setWireFrame(bool toggle);
	void setGUI(bool toggle);

	void setTransMat(const glm::mat4& trans);
	void setRotMat(const glm::mat4& rot);
	void setViewMat(const glm::mat4& view);

	GLuint getPositionTex() { return gPosition; }
	GLuint getNormalTex() { return gNormal; }
	GLuint getColorTex() { return gColorSpec; }
	
private:

	GLuint gBuffer;
	GLuint gPosition = 0, gNormal = 0, gColorSpec = 0;
	GLuint gDepth = 0;

	void initializeBuffer();
	void configureShader();

	enum UNIF {
		TRANS_MAT, ROT_MAT, VIEW_MAT,
		TEXTURE,
		TINT,
		GUI,
		TOTAL
	};
	GLuint uniforms[UNIF::TOTAL];

	static const std::string SHADER_PATH;

};