#pragma once

#include <string>
#include "GL/glew.h"

class Texture {
public:

	Texture() {}
	Texture(GLuint tex, int w, int h) { m_texture = tex;  width = w; height = h; }

	Texture& Load(const std::string& fileName);
	
	GLuint getIndex() { return m_texture; }

	static void unloadAll();

	void bind();

	int getWidth() { return width; }
	int getHeight() { return height; }

	std::string pathway;
private:
	GLuint m_texture;
	int width, height;

	GLuint CreateTexture(const std::string &fileName);
};