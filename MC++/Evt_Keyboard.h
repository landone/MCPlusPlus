#pragma once

#include <SDL2\SDL_keycode.h>
#include <vector>

enum KEY {
	UNDEFINED,
	KEY_W, KEY_A, KEY_S, KEY_D,
	KEY_SPACE,
	KEY_LSHIFT,
	KEY_TOTAL
};

class KeyboardListener {
public:

	KeyboardListener();
	~KeyboardListener();
	
	virtual void onKeyPress(KEY key) {}
	virtual void onKeyRelease(KEY key){}

private:
	std::vector<KeyboardListener*>& listeners;
};

class Evt_Keyboard {
public:

	static void sendKeyPress(SDL_Keycode key);
	static void sendKeyRelease(SDL_Keycode key);

	static bool isKeyDown(KEY key);
	static std::vector<KeyboardListener*>& getListeners() { return listeners; }

private:

	static bool keys[KEY_TOTAL];
	static std::vector<KeyboardListener*> listeners;

	static KEY keyCodeToEnum(SDL_Keycode);

};