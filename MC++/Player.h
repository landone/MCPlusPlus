#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Evt_Display.h"

class World;

class Player : private MouseListener, DisplayListener {
public:

	Player(World&);
	~Player();

	void setPos(float x, float y, float z) { setPos(glm::vec3(x, y, z)); }
	void setPos(glm::vec3 pos) { cam->setPos(pos + glm::vec3(0,height,0)); }
	void move(glm::vec3 amt) { cam->move(amt); }

	glm::vec3 getPos() { return cam->getPos(); }
	Camera* getCamera() { return cam; }

private:

	void onMouseMotion(double, double) override;
	void onMousePress(int button, int x, int y) override;
	void onMouseWheel(double) override;
	void onFrame(double delta) override;

	Camera* cam = Camera::create();
	World& world;

	glm::vec2 sensitivity = glm::vec2(1, 1);
	float acel = 0.2f;
	const float MAX_SPEED = 0.3f;
	int reach = 5;
	float height = 1.5f;
	float width = 0.3f;//Radius

	glm::vec3 velocity;
	float gravity = 0.2f;

};