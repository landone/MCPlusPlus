#include "LightShader.h"
#include "Display.h"

static const std::string SHADER_PATH = "./res/shaders/lightShader";

LightShader::LightShader(GLuint posMap, GLuint normalMap, GLuint colorMap) : Shader(SHADER_PATH){

	maps[0] = posMap;
	maps[1] = normalMap;
	maps[2] = colorMap;

	initializeBuffer();
	configureShader();

}

void LightShader::drawQuad() {

	for (unsigned int i = 0; i < lights.size(); i++) {
		lightColor[i] = lights[i]->getColor();
		lightPos[i] = glm::vec4(lights[i]->getPos(), lights[i]->getRange());
	}

	if (lights.size() > 0) {
		glUniform4fv(uniforms[UNIF::LIGHT_COLOR], lightColor.size(), &lightColor[0][0]);
		glUniform4fv(uniforms[UNIF::LIGHT_POS], lightPos.size(), &lightPos[0][0]);
	}
	glUniform1i(uniforms[UNIF::LIGHT_SIZE], lights.size());

	Shader::drawQuad();

}

Light* LightShader::getLightArray(int& size) {

	size = lights.size();
	return lights[0];

}

Light* LightShader::createLight() {

	if (lights.size() >= MAX_LIGHTS) {
		return nullptr;
	}

	Light* light = Light::create();
	lights.push_back(light);
	lightColor.push_back(light->getColor());
	lightPos.push_back(glm::vec4(light->getPos(), light->getRange()));

	return light;

}

void LightShader::removeLight(Light* light) {

	for (unsigned int i = 0; i < lights.size(); i++) {
		if (lights[i] == light) {

			lights.erase(lights.begin() + i);
			lightColor.erase(lightColor.begin() + i);
			lightPos.erase(lightPos.begin() + i);
			light->destroy();
			break;

		}

	}

}

void LightShader::setCameraPos(glm::vec3 pos) {

	glUniform3fv(uniforms[UNIF::CAM_POS], 1, &pos[0]);

}

void LightShader::updateDimensions(int w, int h) {

	glBindTexture(GL_TEXTURE_2D, outputTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_FLOAT, NULL);

}

void LightShader::configureShader() {

	bindAttrib("position");
	bindAttrib("texCoord");

	uniforms[UNIF::POS_MAP] = createUniform("gPosition");
	uniforms[UNIF::NORM_MAP] = createUniform("gNormal");
	uniforms[UNIF::COLOR_MAP] = createUniform("gColor");

	uniforms[UNIF::LIGHT_COLOR] = createUniform("lightColor");
	uniforms[UNIF::LIGHT_POS] = createUniform("lightPos");
	uniforms[UNIF::LIGHT_SIZE] = createUniform("lightSize");

	uniforms[UNIF::CAM_POS] = createUniform("camPos");

	Shader::bind();//Bind to set default values below

	glUniform1i(uniforms[UNIF::POS_MAP], 0);
	glUniform1i(uniforms[UNIF::NORM_MAP], 1);
	glUniform1i(uniforms[UNIF::COLOR_MAP], 2);
	glUniform1i(uniforms[UNIF::LIGHT_SIZE], 0);

}

void LightShader::initializeBuffer() {

	glGenFramebuffers(1, &myBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, myBuffer);

	glGenTextures(1, &outputTex);
	glBindTexture(GL_TEXTURE_2D, outputTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 0, 0, 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTex, 0);

	static unsigned int attachment = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &attachment);

	//Bind default buffer when done
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void LightShader::bind() {

	Shader::bind();

	glBindFramebuffer(GL_FRAMEBUFFER, myBuffer);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, maps[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, maps[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, maps[2]);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}