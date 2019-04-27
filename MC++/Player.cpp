#include "Player.h"
#include "Evt_Keyboard.h"
#include "World.h"
#include <iostream>

Player::Player(World& wrld) : world(wrld) {

}

Player::~Player() {

	//Rewrite camera to not use pointers
	//cam->destroy();

}

void Player::onMousePress(int button, int x, int y) {

	if (button == 0) {
		glm::vec3 pos = getPos();
		glm::vec3 dir = cam->getForward();
		for (int i = 0; i <= reach; i++) {
			Block* block = world.getBlockAt(pos);
			if (block && block->getMaterial() != AIR) {
				if (block->getMaterial() == COBBLESTONE_MOSSY) {
					block->setMaterial(STONEBRICK);
				}else{
					block->setMaterial(COBBLESTONE_MOSSY);
				}
				break;
			}
			float dist[3];
			bool approx[3];
			dist[0] = floorf(pos[0]);
			approx[0] = pos[0] - dist[0] < 0.00005f;
			dist[0] = dir[0] > 0 ? dist[0] + 1.0f : (approx[0] ? dist[0] - 1.0f : dist[0]);
			dist[0] -= pos[0];
			dist[1] = floorf(pos[1]);
			approx[1] = pos[1] - dist[1] < 0.00005f;
			dist[1] = dir[1] > 0 ? dist[1] + 1.0f : (approx[1] ? dist[1] - 1.0f : dist[1]);
			dist[1] -= pos[1];
			dist[2] = floorf(pos[2]);
			approx[2] = pos[2] - dist[2] < 0.00005f;
			dist[2] = dir[2] > 0 ? dist[2] + 1.0f : (approx[2] ? dist[2] - 1.0f : dist[2]);
			dist[2] -= pos[2];
			float ratios[3];
			ratios[0] = dist[0] / dir[0];
			ratios[1] = dist[1] / dir[1];
			ratios[2] = dist[2] / dir[2];
			if (ratios[0] < ratios[1] && ratios[0] < ratios[2]) {
				pos[0] += dist[0];
				pos[1] += ratios[0] * dir[1];
				pos[2] += ratios[0] * dir[2];
				if (dir[0] <= 0 && !approx[0]) {
					pos[0] -= 0.0001f;
				}
			}
			else if (ratios[1] < ratios[2] && ratios[1] < ratios[0]) {
				pos[1] += dist[1];
				pos[0] += ratios[1] * dir[0];
				pos[2] += ratios[1] * dir[2];
				if (dir[1] <= 0 && !approx[1]) {
					pos[1] -= 0.0001f;
				}
			}
			else {
				pos[2] += dist[2];
				pos[1] += ratios[2] * dir[1];
				pos[0] += ratios[2] * dir[0];
				if (dir[2] < 0 && !approx[2]) {
					pos[2] -= 0.0001f;
				}
			}
		}
	}

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