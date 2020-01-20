#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Evt_Display.h"
#include "Block.h"
#include "Inventory.h"
#include "MDL_Human.h"

class World;

enum VIEW_MODE {
	FIRST_PERSON,
	THIRD_PERSON,
	THIRD_PERSON_FRONT
};

class Player : private MouseListener, DisplayListener {
public:

	Player(World&);
	~Player();

	void setPos(float x, float y, float z) { setPos(glm::vec3(x, y, z)); }
	void setPos(glm::vec3 pos);
	void move(float x, float y, float z) { move(glm::vec3(x, y, z)); }
	void move(glm::vec3 amt) { setPos(getPos() + amt); }
	void setHand(int index);
	void setViewMode(VIEW_MODE);

	glm::vec3 getPos() { return m_position; }
	Camera* getCamera() { return cam; }

private:

	void onMouseMotion(double, double) override;
	void onMousePress(int button, int x, int y) override;
	void onMouseWheel(double) override;
	void onFrame(double delta) override;
	void onDrawGUI(GBuffer& gBuffer) override;

	Camera* cam = Camera::create();
	VIEW_MODE viewMode = FIRST_PERSON;
	float thirdpersonDistance = 3.0f;
	MDL_Human model;

	Graphic crosshair, hotbar, hotbarSelect;
	
	glm::vec3 m_position;
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
	float width = 0.45f;//Radius

	glm::vec3 velocity;
	float gravity = 0.4f;
	float friction = 0.4f;
	float jumpStrength = 0.1f;
	Block* floorBlock = nullptr;

};