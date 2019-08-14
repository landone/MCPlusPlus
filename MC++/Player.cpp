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
		text->setSize(0.08f);
		text->setColor(glm::vec3(1, 1, 0));
		//text->getGraphic().trans.SetPos(glm::vec3(500, 0.4, 0));
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
	pastItem.getTrans().SetPos(handPos);
	pastItem.setPhysical(false);
	pastItem.setGUI(false);
	ItemStack& item = inven.getItem(index);
	if ((item.isBlock() && item.getMaterial() != MATERIAL::AIR) ||
		(!item.isBlock() && item.getType() != ITEM::NOTHING)) { //Make visible if real
		item.setPhysical(true);
		item.setGUI(true);
	}
	handIndex = index;

	handPos = item.getTrans().GetPos();
	text->setString(item.getName());
	text->getGraphic().trans.SetPos(glm::vec3(-text->getGraphic().trans.GetScale().x, -0.8, 0));

}

void Player::onMousePress(int button, int x, int y) {

	glm::vec3 headPos = m_position + glm::vec3(0, height, 0);
	glm::vec3 pos;
	Block* block = world.traceRay(headPos, cam->getForward(), 5, button == 2, &pos);
	if (button == 0 && block) {//Left click
		if (block->getMaterial() != MATERIAL::AIR) {
			world.spawnItem(block->getMaterial(), block->getPosition());
		}
		block->setMaterial(MATERIAL::AIR);
		world.updateVisibility(block);
	}
	else if (button == 2 && block) {//Right click
		ItemStack& hand = inven.getItem(handIndex);
		if (!hand.isBlock() || hand.getMaterial() == MATERIAL::AIR) {
			return;
		}
		glm::vec3 bPos = block->getPosition();
		//Check for attempt to place block on self
		if (button == 2 && bPos.x == floorf(headPos.x) && bPos.z == floorf(headPos.z) &&
			(bPos.y == floorf(headPos.y) || bPos.y == floorf(headPos.y - 1))) {
			return;
		}
		block->setMaterial(hand.getMaterial());
		world.updateVisibility(block);
	}
	else if (button == 1) {//Middle click
		thirdperson(!isThirdperson);
	}
}

void Player::onMouseWheel(double amt) {

	setHand((handIndex + (amt > 0 ? 1 : inven.size() - 1)) % inven.size());

}

void Player::onMouseMotion(double x, double y) {
	
	cam->rotate(glm::vec3(y / 1000 * sensitivity.y, -x / 1000 * sensitivity.x, 0));

}

void Player::onFrame(double delta) {

	if (isThirdperson) {
		model.setArmRotation(glm::vec3(sin(walkCounter*2)*0.4f, 0, 0), false);
		model.setArmRotation(glm::vec3(-sin(walkCounter * 2)*0.4f, 0, 0), true);
		model.setLegRotation(glm::vec3(-sin(walkCounter * 2)*0.4f, 0, 0), false);
		model.setLegRotation(glm::vec3(sin(walkCounter * 2)*0.4f, 0, 0), true);
		model.setHeadRotation(glm::vec3(-cam->getRot().x, 0, 0));
		model.setBodyRotation(glm::vec3(0, cam->getRot().y + 3.1415f, 0));
	}

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
		velocity.y -= gravity * (float)delta;
	}


	floorBlock = nullptr; //Reset

	glm::vec3 pos = getPos();
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
		for (unsigned int i = 0; i < collisions.size(); i++) {
			if (glm::distance(pos, collisions[i]) < distance) {
				distance = glm::distance(pos, collisions[i]);
				closest = collisions[i];
			}
		}

		glm::vec3 colDir = glm::normalize(pos - closest);
		setPos(closest + colDir * width);

	}

	move(velocity);

}

void Player::setPos(glm::vec3 pos) {

	m_position = pos;
	cam->setPos(m_position + glm::vec3(0, height, 0));
	if (isThirdperson) {
		model.setPos(pos - glm::vec3(0, width, 0));
	}

}

void Player::thirdperson(bool set) {
	isThirdperson = set;
	model.setVisible(set);
	if (set) {
		cam->setOffset(thirdpersonDistance);
		model.setPos(m_position - glm::vec3(0, width, 0));
	}
	else {
		cam->setOffset(0.0f);
	}
}