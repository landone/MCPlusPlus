#include "Texture.h"
#include <iostream>
#include <map>
#include "stb_image.h"

static std::map<std::string, GLuint> globals;
static GLuint lastTexture = NULL;

std::string LowerCase(std::string source) {
	const char* arr = source.c_str();
	std::string result = "";
	for (unsigned int i = 0; i < source.length(); i++) {
		result += tolower(arr[i]);
	}
	return result;
}

GLuint Texture::lastBound() {
	return lastTexture;
}

GLuint Texture::CreateTexture(const std::string &fileName) {
	int numComp;
	GLuint result;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComp, 4);
	if (imageData == NULL) {
		std::cout << "Texture file doesn't exist: " << fileName << std::endl;
		return 0;
	}
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Repeat texture width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//Repeat texture height

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Minify texture
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Magnify texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Minify texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Magnify texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
	return result;
}

Texture& Texture::Load(const std::string& fileName) {
	pathway = LowerCase(fileName);
	if (globals.find(pathway) != globals.end()) {
		m_texture = globals[pathway];
	}
	else {
		m_texture = CreateTexture(pathway);
		globals[pathway] = m_texture;
	}
	return *this;
}

void Texture::unloadAll() {
	for (const auto& pair : globals) {
		glDeleteTextures(1, &pair.second);
	}
	globals.clear();
}

void Texture::bind() {
	//assert(unit >= 0 && unit <= 31);
	//glActiveTexture(GL_TEXTURE0 + unit);
	//if (lastTexture != m_texture) {//Only bind if necessary
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		lastTexture = m_texture;
	//}
}