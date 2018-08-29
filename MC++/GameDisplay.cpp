#include "GameDisplay.h"
#include <iostream>

void GameDisplay::setSize(int w, int h) {

	Display::setSize(w, h);
	updateDimensions(w, h);

}

void GameDisplay::updateDimensions(int w, int h) {

	gBuffer.updateDimensions(w, h);
	lightShader.updateDimensions(w, h);
	postProcessor.updateDimensions(w, h);

}

GameDisplay::GameDisplay(int width, int height, const std::string& title) : Display(width, height, title), 
gBuffer(), lightShader(gBuffer.getPositionTex(), gBuffer.getNormalTex(), gBuffer.getColorTex()), postProcessor(lightShader.getTex()) {

	updateDimensions(width, height);

}

GameDisplay::GameDisplay(int width, int height) : Display(width, height),
gBuffer(), lightShader(gBuffer.getPositionTex(), gBuffer.getNormalTex(), gBuffer.getColorTex()), postProcessor(lightShader.getTex()) {

	updateDimensions(width, height);

}

GameDisplay::GameDisplay(const std::string& title) : Display(title),
gBuffer(), lightShader(gBuffer.getPositionTex(), gBuffer.getNormalTex(), gBuffer.getColorTex()), postProcessor(lightShader.getTex()) {

	int width = getWidth();
	int height = getHeight();

	updateDimensions(width, height);

}

GameDisplay::GameDisplay() : Display(),
gBuffer(), lightShader(gBuffer.getPositionTex(), gBuffer.getNormalTex(), gBuffer.getColorTex()), postProcessor(lightShader.getTex()) {

	int width = getWidth();
	int height = getHeight();

	updateDimensions(width, height);

}