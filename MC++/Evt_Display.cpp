#include "Evt_Display.h"
#include <vector>
#include <algorithm>

static std::vector<DisplayListener*> listeners;

DisplayListener::DisplayListener() {
	listeners.push_back(this);
}

DisplayListener::~DisplayListener() {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());
}

void Evt_Display::sendFrame(double delta) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onFrame(delta);
	}
}

void Evt_Display::sendDrawGUI(GBuffer& gBuffer) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDrawGUI(gBuffer);
	}
}

void Evt_Display::sendDrawGeometry(GBuffer& gBuffer) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDrawGeometry(gBuffer);
	}
}