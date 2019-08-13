#include "Player.h"
#include "Evt_Keyboard.h"
#include "World.h"
#include "Graphic.h"
#include "GameAssetLoader.h"
#include "ItemStack.h"
#include <iostream>

static Text* text = nullptr;

Player::Player(World& wrld) : world(wrld), inven(9) {

	if (text == nullptr) {
		text = new Text();
		text->setSize(0.08);
		text->setColor(glm::vec3(1, 1, 0));
	}

	for (int i = 1; i < ITEM::MAX_ITEM; i++) {
		inven.setItem(i-1, (ITEM)i);
	}

	inven.setItem(7, MATERIAL::COBBLESTONE);
	inven.setItem(8, MATERIAL::PLANKS_OAK);

	setHand(0);

}

Player::~Player() {

	//Rewrite camera to not use pointers
	//cam->destroy();

}

void Player::setHand(int index) {

	ItemStack& pastItem = inven.getItem(handIndex);
	pastItem.setPhysical(false);
	pastItem.setGUI(false);
	pastItem.getTrans().SetPos(handPos);
	ItemStack& item = inven.getItem(index);
	if ((item.isBlock() && item.getMaterial() != MATERIAL::AIR) ||
		(!item.isBlock() && item.getType() != ITEM::NOTHING)) { //Make visible if real
		item.setPhysical(true);
		item.setGUI(true);
	}
	handIndex = index;

	handPos = item.getTrans().GetPos();
	text->setString(item.getName());

}

void Player::onMousePress(int button, int x, int y) {

	glm::vec3 myPos = getPos();
	glm::vec3 pos;
	Block* block = world.traceRay(myPos, cam->getForward(), 5, button == 2, &pos);
	if (block) {
		if (button == 0) {//Left click
			block->setMaterial(MATERIAL::AIR);
			world.updateVisibility(block);
		}
		else if (button == 2) {//Right click
			ItemStack& hand = inven.getItem(handIndex);
			if (!hand.isBlock() || hand.getMaterial() == MATERIAL::AIR) {
				return;
			}
			glm::vec3 bPos = block->getPosition();
			//Check for attempt to place block on self
			if (button == 2 && bPos.x == floorf(myPos.x) && bPos.z == floorf(myPos.z) &&
				(bPos.y == floorf(myPos.y) || bPos.y == floorf(myPos.y - 1))) {
				return;
			}
			block->setMaterial(hand.getMaterial());
			world.updateVisibility(block);
		}
		else if (button == 1) {//Middle click
			setPos(pos + glm::vec3(0, 2, 0));
		}
	}
}

void Player::onMouseWheel(double amt) {

	setHand((handIndex + (amt > 0 ? 1 : inven.size() - 1)) % inven.size());

}

void Player::onMouseMotion(double x, double y) {
	
	cam->rotate(glm::vec3(y / 1000 * sensitivity.y, -x / 1000 * sensitivity.x, 0));

}

void Player::onFrame(double delta) {

	int forMul = Evt_Keyboard::isKeyDown(KEY_W) ? 1 : (Evt_Keyboard::isKeyDown(KEY_S) ? -1 : 0);
	int rightMul = Evt_Keyboard::isKeyDown(KEY_D) ? 1 : (Evt_Keyboard::isKeyDown(KEY_A) ? -1 : 0);
	ItemStack& item = inven.getItem(handIndex);
	//Accelerate
	if (forMul != 0 || rightMul != 0) {

		walking = true;
		walkCounter += 0.05f;
		item.getTrans().SetPos(handPos + glm::vec3(0,sinf(walkCounter)*0.05f,0));

		glm::vec3 forward = cam->getForward();
		forward.y = 0;//No height component
		forward = glm::normalize(forward);

		glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0));

		forward *= forMul;
		right *= rightMul;

		if (glm::length(velocity) < maxRunSpeed) { //Don't accelerate further than max speed
			velocity += glm::normalize(forward + right) * (floorBlock ? acel : airAcel) * (float)delta;
		}

	}
	else if(walking) {
		walking = false;
		walkCounter = 0.0f;
		item.getTrans().SetPos(handPos);
	}

	if (floorBlock) {//On ground

		//Friction
		glm::vec2 flatVel = glm::vec2(velocity.x, velocity.z);
		if (glm::length(flatVel) > 0.0f) {
			flatVel = glm::normalize(flatVel) * glm::max(0.0f, glm::length(flatVel) - friction * (float)delta);
		}
		velocity = glm::vec3(flatVel.x, velocity.y, flatVel.y);

		if (Evt_Keyboard::isKeyDown(KEY_SPACE)) {//Jump
			velocity.y += jumpStrength;
		}

	}
	else {
		velocity.y -= gravity * delta;
	}


	floorBlock = nullptr; //Reset

	glm::vec3 pos = cam->getPos() - glm::vec3(0,height,0);
	glm::vec3 point, axis;
	bool checkAgain = true;
	std::vector<glm::vec3> collisions;
	while (checkAgain && world.traceRay(pos, glm::normalize(velocity), glm::length(velocity) + width, false, &point, &axis) != nullptr) {
		
		if (glm::distance(pos, point) > 0.0f) {
			collisions.push_back(point);
		}
		checkAgain = glm::length(axis) == 1.0f;
		velocity -= glm::dot(velocity, axis) * axis;

	}

	if (world.traceRay(pos, glm::vec3(0, -1, 0), width, false, &point, nullptr) != nullptr) {
		floorBlock = world.getBlockAt(pos);
		if (glm::distance(pos, point) > 0.0f) {
			collisions.push_back(point);
		}
	}

	if (collisions.size() > 0) {
		glm::vec3 closest;
		float distance = INFINITY;
		for (int i = 0; i < collisions.size(); i++) {
			if (glm::distance(pos, collisions[i]) < distance) {
				distance = glm::distance(pos, collisions[i]);
				closest = collisions[i];
			}
		}

		glm::vec3 colDir = glm::normalize(pos - closest);
		setPos(closest + colDir * width);

	}

	cam->move(velocity);

}