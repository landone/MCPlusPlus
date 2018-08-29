#include "Player.h"
#include "Evt_Keyboard.h"

#include <iostream>

Player::Player() {

	

}

Player::~Player() {

	//Rewrite camera to not use pointers
	//cam->destroy();

}

void Player::onMouseMotion(double x, double y) {
	
	cam->rotate(glm::vec3(y / 1000 * sensitivity.y, -x / 1000 * sensitivity.x, 0));

}

void Player::onMouseWheel(double amt) {

	static const double MAX = PI * 180 / 360;
	static const double MIN = PI * 10 / 360;

	double fov = cam->getFOV() + amt / 100;
	fov = glm::max(MIN, glm::min(MAX, fov));

	cam->setFOV(fov);

}

void Player::onFrame(double delta) {

	glm::vec3 output;

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

		output += glm::normalize(forward + right) * speed * (float)delta;

	}

	output.y += heightMul * speed * (float)delta;

	cam->move(output);

}