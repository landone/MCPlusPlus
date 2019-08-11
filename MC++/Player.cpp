#include "Player.h"
#include "Evt_Keyboard.h"
#include "World.h"
#include "Graphic.h"
#include "GameAssetLoader.h"
#include "ItemStack.h"
#include <iostream>

static MATERIAL chosenMat = BEDROCK;
static ItemStack* item = nullptr;
static Graphic* graphic = nullptr;
static Text* text = nullptr;

Player::Player(World& wrld) : world(wrld) {
	if (item == nullptr) {
		item = new ItemStack(chosenMat);
		item->setPhysical(true);
		item->setGUI(true);
		text = new Text(item->getName());
		text->setSize(0.08);
		text->setColor(glm::vec3(1, 1, 0));
	}
	//graphic->trans.SetScale(glm::vec3(0.09,0.16,1));
	//graphic->trans.SetPos(glm::vec3(-1, -1, -1));
}

Player::~Player() {

	//Rewrite camera to not use pointers
	//cam->destroy();

}

void Player::onMousePress(int button, int x, int y) {

	glm::vec3 pos;
	Block* block = world.traceRay(getPos(), cam->getForward(), 5, button == 2, &pos);
	if (button == 0 || button == 2) {
		if (block) {
			MATERIAL mat = button == 0 ? AIR : chosenMat;
			block->setMaterial(mat);
			world.updateVisibility(block);
		}
	}
	else if (button == 1 && !(pos.x == 0 && pos.y == 0 && pos.z == 0)) {
		setPos(pos + glm::vec3(0,2,0));
	}

}

void Player::onMouseWheel(double amt) {

	chosenMat = (MATERIAL)(((int)chosenMat - 1 + (amt > 0 ? 1 : MATERIAL::MAX_MAT - 2)) % (MATERIAL::MAX_MAT - 1) + 1);
	//graphic->setTexture(GameAssetLoader::getMaterial(chosenMat));
	item->setMaterial(chosenMat);
	text->setString(item->getName());

	/*static const double MAX = PI * 180 / 360;
	static const double MIN = PI * 10 / 360;

	double fov = cam->getFOV() + amt / 100;
	fov = glm::max(MIN, glm::min(MAX, fov));

	cam->setFOV(fov);*/

}

void Player::onMouseMotion(double x, double y) {
	
	cam->rotate(glm::vec3(y / 1000 * sensitivity.y, -x / 1000 * sensitivity.x, 0));

}

void Player::onFrame(double delta) {

	int forMul = Evt_Keyboard::isKeyDown(KEY_W) ? 1 :(Evt_Keyboard::isKeyDown(KEY_S) ? -1 : 0);
	int rightMul = Evt_Keyboard::isKeyDown(KEY_D) ? 1 : (Evt_Keyboard::isKeyDown(KEY_A) ? -1 : 0);
	int heightMul = Evt_Keyboard::isKeyDown(KEY_SPACE) ? 1 : (Evt_Keyboard::isKeyDown(KEY_LSHIFT) ? -1 : 0);

	if (forMul != 0 || rightMul != 0) {

		glm::vec3 forward = cam->getForward();
		forward.y = 0;//No height component
		forward = glm::normalize(forward);

		glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0));

		forward *= forMul;
		right *= rightMul;

		velocity += glm::normalize(forward + right) * acel * (float)delta;

	}

	velocity.y -= gravity;

	glm::vec3 pos = cam->getPos() - glm::vec3(0,height,0);
	glm::vec3 point, axis;
	bool checkAgain = true;
	while (checkAgain && world.traceRay(pos, glm::normalize(velocity), glm::length(velocity) + width, false, &point, &axis) != nullptr) {
		
		/*if (axis.y != 1.0f) {
			std::cout << "axis: (" << axis.x << ", " << axis.y << ", " << axis.z << ")\n";
		}*/
		
		/*std::cout << "dot: " << glm::dot((point - pos), axis) << std::endl;*/
		checkAgain = glm::length(axis) == 1.0f;
		cam->setPos(point + glm::vec3(0, height, 0) - glm::normalize(velocity) * width);
		velocity -= glm::dot(velocity, axis) * axis;

	}

	//velocity.y += heightMul * acel * (float)delta;
	if (glm::length(velocity) > MAX_SPEED) {
		velocity = glm::normalize(velocity)* MAX_SPEED;
	}

	cam->move(velocity);
	glm::vec3 npos = cam->getPos() + glm::vec3(0, -height, 0);
	/*static int counter = 0;
	if (counter < 15) {
		counter++;
		std::cout << "pos: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
		std::cout << "point: (" << point.x << ", " << point.y << ", " << point.z << ")\n";
		std::cout << "new pos: (" << npos.x << ", " << npos.y << ", " << npos.z << ")\n";
		std::cout << "velocity: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")\n";
	}*/

}