#pragma once

enum FONT {
	ASCII = 0,
	MAX_FONT
};

#include "Graphic.h"
#include "BasicShader.h"
#include "GameAssetLoader.h"

class Text {
public:

	Text(std::string = "");

	void setColor(glm::vec3);
	void setString(std::string);
	void setFont(FONT);
	void setSize(float height);

	Graphic& getGraphic() { return graphic; }
	Texture& getTexture() { return tex; }
	Transform& getTransform() { return graphic.trans; }
	glm::vec3 getColor() { return color; }
	std::string getString() { return text; }
	FONT getFont() { return font_enum; }

private:
	Graphic graphic;
	GLuint buf; //One buffer for all text
	Texture tex;
	Texture font;
	glm::vec3 color = glm::vec3(1, 1, 1);
	std::string text;
	FONT font_enum;

	void createTexture();

	BasicShader* shader = nullptr;

};