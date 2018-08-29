#include "Evt_Mouse.h"
#include <iostream>
#include <vector>
#include <algorithm>

static std::vector<MouseListener*> listeners;

static bool buttons[3];

MouseListener::MouseListener() {
	listeners.push_back(this);
}

MouseListener::~MouseListener() {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());
}

void Evt_Mouse::sendMouseMotion(double xrel, double yrel) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onMouseMotion(xrel, yrel);
	}
}

void Evt_Mouse::sendMousePress(int button, int x, int y) {
	buttons[button] = true;
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onMousePress(button, x, y);
	}
}

void Evt_Mouse::sendMouseRelease(int button, int x, int y) {
	buttons[button] = false;
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onMouseRelease(button, x, y);
	}
}

bool Evt_Mouse::sendPreMousePress(int button, int x, int y) {
	buttons[button] = true;
	bool output = true;
	for (unsigned int i = 0; i < listeners.size(); i++) {
		if (!listeners[i]->onPreMousePress(button, x, y)) {
			output = false;
		}
	}
	return output;
}

bool Evt_Mouse::sendPreMouseRelease(int button, int x, int y) {
	buttons[button] = false;
	bool output = true;
	for (unsigned int i = 0; i < listeners.size(); i++) {
		if (!listeners[i]->onPreMouseRelease(button, x, y)) {
			output = false;
		}
	}
	return output;
}

void Evt_Mouse::sendMouseWheel(double amount) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onMouseWheel(amount);
	}
}

bool Evt_Mouse::isButtonHeld(int button) {
	return buttons[button % 3];
}