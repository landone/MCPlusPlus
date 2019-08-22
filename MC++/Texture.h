#pragma once

#include <string>
#include "GL/glew.h"

class Texture {
public:

	Texture() {}
	Texture(std::string path) { Load(path); }
	Texture(GLuint tex, int w, int h) { m_texture = tex;  width = w; height = h; }

	Texture& Load(const std::string& fileName);
	
	void setIndex(GLuint tex) { m_texture = tex; }
	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }

	static void unloadAll();

	void bind();

	GLuint getIndex() { return m_texture; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	std::string pathway;
private:
	GLuint m_texture = 0;
	int width = 0, height = 0;

	GLuint CreateTexture(const std::string &fileName);
};