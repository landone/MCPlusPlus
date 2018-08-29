#pragma once

class MouseListener {
public:

	MouseListener();
	~MouseListener();

	virtual void onMouseMotion(double x, double y) {}
	virtual void onMousePress(int button, int x, int y) {}
	virtual void onMouseRelease(int button, int x, int y){}
	virtual bool onPreMousePress(int button, int x, int y) { return true; }
	virtual bool onPreMouseRelease(int button, int x, int y) { return true; }
	virtual void onMouseWheel(double amount) {}

};

class Evt_Mouse {
public:

	static void sendMouseMotion(double xrel, double yrel);
	static void sendMousePress(int button, int x, int y);
	static void sendMouseRelease(int button, int x, int y);
	static bool sendPreMousePress(int button, int x, int y);
	static bool sendPreMouseRelease(int button, int x, int y);
	static void sendMouseWheel(double amount);

	static bool isButtonHeld(int button);
};