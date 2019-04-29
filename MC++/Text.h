#pragma once

#include "Graphic.h"
#include "TextShader.h"

class Text {
public:

	Text(std::string);
	Graphic& getGraphic() { return graphic; }
	Texture& getTexture() { return tex; }
	Transform& getTransform() { return graphic.trans; }

private:
	Graphic graphic;
	Texture tex;
	Texture font;
	std::string text;

	void createTexture();

	TextShader shader; //Eventually change text shader to not reload shader program each instance

};