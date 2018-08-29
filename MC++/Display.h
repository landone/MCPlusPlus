#pragma once

#include <SDL2/SDL.h>
#include <glm\glm.hpp>
#undef main
#include <string>

class Display {
public:

	Display();
	Display(const std::string& title);
	Display(int width, int height);
	Display(int width, int height, const std::string& title);
	~Display();

	void clear(double r, double g, double b, double a = 1.0);
	void update();
	bool isOpen() { return !isClosed; }

	int getWidth() { return width; }
	int getHeight() { return height; }

	void setBorder(bool toggle) { SDL_SetWindowBordered(window, (SDL_bool)toggle); }
	void setTitle(const std::string& title);
	virtual void setSize(int width, int height);
	void setSize(glm::vec2 dimensions) { setSize((int)dimensions.x, (int)dimensions.y); }
	void setFullscreen(bool toggle);
	void setOpacity(float opacity) { SDL_SetWindowOpacity(window, opacity); }

	void center();
	void hideCursor(bool toggle);
	void relativeCursor(bool toggle);


private:
	int width, height;
	bool isClosed;
	SDL_GLContext glContext;
	SDL_Window* window;
};