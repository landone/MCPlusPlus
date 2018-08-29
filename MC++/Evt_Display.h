#pragma once

#include "GBuffer.h"

class DisplayListener {
public:

	DisplayListener();
	~DisplayListener();

	virtual void onFrame(double delta) {}
	virtual void onDrawGUI(GBuffer& gBuffer) {}
	virtual void onDrawGeometry(GBuffer& gBuffer) {}

};

class Evt_Display {
public:

	static void sendFrame(double delta);
	static void sendDrawGUI(GBuffer& gBuffer);
	static void sendDrawGeometry(GBuffer& gBuffer);

};