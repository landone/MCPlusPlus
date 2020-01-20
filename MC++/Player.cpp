#include "Player.h"
#include "Evt_Keyboard.h"
#include "World.h"
#include "Graphic.h"
#include "GameAssetLoader.h"
#include "ItemStack.h"
#include <iostream>

static Text* text = nullptr;

Player::Player(World& wrld) : world(wrld), inven(9), crosshair(GameAssetLoader::getGUI(GUI_CROSSHAIR)),
hotbar(GameAssetLoader::getGUI(GUI_HOTBAR)), hotbarSelect(GameAssetLoader::getGUI(GUI_HOTBAR_SELECT)) {

	hotbar.trans.SetPos(glm::vec3(hotbar.trans.GetPos().x, -1, 0));
	hotbarSelect.trans.SetPos(hotbar.trans.GetPos());
	model.setVisible(false);
	
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

	if (index < 0 || index >= 9) {//Hotbar limits
		return;
	}

	glm::vec3 selectPos = hotbar.trans.GetPos();
	selectPos.x += index * hotbar.trans.GetScale().x * 2 / 9.0f;
	hotbarSelect.trans.SetPos(selectPos);

	ItemStack& pastItem = inven.getItem(handIndex);
	pastItem.getTrans().SetPos(handPos);
	pastItem.setPhysical(false);
	pastItem.setGUI(false);
	ItemStack& item = inven.getItem(index);
	if ((item.isBlock() && item.getMaterial() != MATERIAL::AIR) ||
		(!item.isBlock() && item.getType() != ITEM::NOTHING)) { //Make visible if real
		item.setPhysical(true);
		item.setGUI(viewMode == VIEW_MODE::FIRST_PERSON);
	}
	handIndex = index;

	handPos = item.getTrans().GetPos();
	//text->setString(item.getName());
	//text->getGraphic().trans.SetPos(glm::vec3(-text->getGraphic().trans.GetScale().x, -0.8, 0));

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
		setViewMode(viewMode == VIEW_MODE::FIRST_PERSON ? VIEW_MODE::THIRD_PERSON : 
			(viewMode == VIEW_MODE::THIRD_PERSON ? VIEW_MODE::THIRD_PERSON_FRONT : VIEW_MODE::FIRST_PERSON));
	}
}

void Player::onDrawGUI(GBuffer& gBuffer) {

	Mesh& mesh = (*Graphic::getQuadMesh());
	Transform trans;
	glm::vec3 hotScale = hotbar.trans.GetScale();
	trans.SetScale(glm::vec3(hotScale.x / 9.0f, hotScale.y, 1.0f));
	gBuffer.setRotMat(trans.GetRotMatrix());//Set rot to identity
	for (int i = 0; i < 9; i++) {
		if (!inven.getItem(i).isNothing()) {
			trans.SetPos(hotbar.trans.GetPos() + glm::vec3(i * hotScale.x * 2 / 9.0f, 0, 0));
			gBuffer.setTransMat(trans.GetMatrix());
			inven.getItem(i).getTexture().bind();
			mesh.draw();
		}
	}

}

void Player::onMouseWheel(double amt) {

	setHand((handIndex + (amt > 0 ? inven.size() - 1 : 1)) % inven.size());

}

void Player::onMouseMotion(double x, double y) {
	
	cam->rotate(glm::vec3(y / 1000 * sensitivity.y, -x / 1000 * sensitivity.x, 0));

}

void Player::onFrame(double delta) {

	ItemStack& item = inven.getItem(handIndex);
	if (viewMode != VIEW_MODE::FIRST_PERSON) { //Model rotations
		model.setArmRotation(glm::vec3(sin(walkCounter*2)*0.4f, 0, 0), false);
		model.setArmRotation(glm::vec3(-sin(walkCounter * 2)*0.4f, 0, 0), true);
		model.setLegRotation(glm::vec3(-sin(walkCounter * 2)*0.4f, 0, 0), false);
		model.setLegRotation(glm::vec3(sin(walkCounter * 2)*0.4f, 0, 0), true);
		model.setHeadRotation(glm::vec3(-cam->getRot().x, 0, 0));
		model.setBodyRotation(glm::vec3(0, cam->getRot().y + 3.1415f, 0));
		if (item.isBlock()) {
			item.getTrans().SetRot(glm::vec3(0, 3.1415 / 2.0f + model.getArmRot().y, 0));
		}
		else {
			item.getTrans().SetRot(glm::vec3(-3.1415f, -3.1415 / 2.0f - model.getArmRot().y, -3.1415f));
		}
	}
	
	int forMul = Evt_Keyboard::isKeyDown(KEY_W) ? 1 : (Evt_Keyboard::isKeyDown(KEY_S) ? -1 : 0);
	int rightMul = Evt_Keyboard::isKeyDown(KEY_D) ? 1 : (Evt_Keyboard::isKeyDown(KEY_A) ? -1 : 0);
	//Accelerate
	if (forMul != 0 || rightMul != 0) {

		walking = true;
		walkCounter += 0.05f;
		if (viewMode == VIEW_MODE::FIRST_PERSON) {
			item.getTrans().SetPos(handPos + glm::vec3(0, sinf(walkCounter) * 0.05f, 0));
		}

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
			velocity = glm::vec3(flatVel.x, velocity.y, flatVel.y);
		}
		/* TODO: Replace with and implement isKeyPressed */
		if (Evt_Keyboard::isKeyDown(KEY_SPACE)) {//Jump
			velocity.y += jumpStrength;
		}

	}
	else {
		velocity.y -= gravity * (float)delta;
	}

	glm::vec3 pos = getPos();
	floorBlock = nullptr; //Reset
	/* Check for current collisions */
	for (int i = 0; i < 6; i++) {
		glm::vec3 norm;
		switch (i) {
		case 0:
			norm = glm::vec3(-1, 0, 0);
			break;
		case 1:
			norm = glm::vec3(1, 0, 0);
			break;
		case 2:
			norm = glm::vec3(0, -1, 0);
			break;
		case 3:
			norm = glm::vec3(0, 1, 0);
			break;
		case 4:
			norm = glm::vec3(0, 0, -1);
			break;
		case 5:
			norm = glm::vec3(0, 0, 1);
			break;
		}
		Block* col = world.traceRay(pos, norm, width, false, nullptr, nullptr);
		if (i == 2) {
			floorBlock = col;
		}
		if (col) {
			float component = glm::dot(velocity, norm);
			/* If component in correct direction */
			if (component > 0) {
				velocity -= component * norm;
			}
		}
	}
	/* Check for incoming collisions */
	glm::vec3 point, axis;
	bool checkAgain = true;
	std::vector<glm::vec3> collisions;
	Block* lastBlock = nullptr;
	Block* currBlock = nullptr;
	while (checkAgain && (currBlock = world.traceRay(pos, glm::normalize(velocity), glm::length(velocity) + width, false, &point, &axis)) != nullptr) {

		if (axis.y == 1) {
			floorBlock = currBlock;
		}

		if (lastBlock == currBlock) {
			/* Save us from raytracing purgatory */
			velocity += axis * 0.0005f;
			lastBlock = currBlock;
			continue;
		}
		lastBlock = currBlock;

		float dist = glm::distance(pos, point);
		collisions.push_back(point);
		checkAgain = glm::length(axis) == 1.0f;
		float component = glm::dot(velocity, axis);
		float ratio = glm::clamp((1 - ((dist - width) / abs(component))), 0.0f, 1.0f);
		velocity -= (component * ratio) * axis;

	}

	/* Find closest collision point */
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
		//setPos(closest + colDir * width);

	}

	move(velocity);

}

void Player::setPos(glm::vec3 pos) {

	m_position = pos;
	cam->setPos(m_position + glm::vec3(0, height, 0));
	if (viewMode != VIEW_MODE::FIRST_PERSON) {
		model.setPos(pos - glm::vec3(0, width, 0));
		ItemStack& item = inven.getItem(handIndex);
		item.getTrans().SetPos(model.getHandPos(true, !item.isBlock()));
	}

}

void Player::setViewMode(VIEW_MODE mode) {
	viewMode = mode;
	if (viewMode != VIEW_MODE::FIRST_PERSON) {
		cam->setOffset(thirdpersonDistance * (viewMode == VIEW_MODE::THIRD_PERSON ? 1.0f : -1.0f));
		model.setPos(m_position - glm::vec3(0, width, 0));
		model.setVisible(true);
	}
	else {
		cam->setOffset(0.0f);
		model.setVisible(false);
	}
	setHand(handIndex);
}