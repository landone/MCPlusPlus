#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Evt_Display.h"

class Player : public MouseListener, DisplayListener {
public:

	Player();
	~Player();

	void setPos(float x, float y, float z) { setPos(glm::vec3(x, y, z)); }
	void setPos(glm::vec3 pos) { cam->setPos(pos); }
	void move(glm::vec3 amt) { cam->move(amt); }

	glm::vec3 getPos() { return cam->getPos(); }
	Camera* getCamera() { return cam; }

	void onMouseMotion(double, double) override;
	void onMouseWheel(double) override;

	void onFrame(double delta) override;//Add movement here

private:

	Camera* cam = Camera::create();

	glm::vec2 sensitivity = glm::vec2(1, 1);
	float speed = 4.317f;

};