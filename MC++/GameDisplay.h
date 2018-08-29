#pragma once

#include "Display.h"
#include "GBuffer.h"
#include "LightShader.h"
#include "PostProcessor.h"

class GameDisplay : public Display {
public:

	GameDisplay();
	GameDisplay(const std::string& title);
	GameDisplay(int width, int height);
	GameDisplay(int width, int height, const std::string& title);

	void setSize(int width, int height) override;

	GBuffer gBuffer;
	LightShader lightShader;
	PostProcessor postProcessor;

private:

	void updateDimensions(int w, int h);

};