#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Evt_Display.h"
#include "Block.h"
#include "Inventory.h"

class World;

class Player : private MouseListener, DisplayListener {
public:

	Player(World&);
	~Player();

	void setPos(float x, float y, float z) { setPos(glm::vec3(x, y, z)); }
	void setPos(glm::vec3 pos) { cam->setPos(pos + glm::vec3(0,height,0)); }
	void setHand(int index);
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

	Inventory inven;
	int handIndex = 0;

	bool walking = false;
	glm::vec3 handPos;
	float walkCounter = 0.0f;

	glm::vec2 sensitivity = glm::vec2(1, 1);
	float acel = 0.75f;
	float airAcel = 0.1f;
	float maxRunSpeed = 0.12f;
	int reach = 5;
	float height = 1.5f;
	float width = 0.3f;//Radius

	glm::vec3 velocity;
	float gravity = 0.4f;
	float friction = 0.4f;
	float jumpStrength = 0.05f;
	Block* floorBlock = nullptr;

};