#include "Camera.h"
#include <iostream>
#include <algorithm>

#define RIGHT_ANGLE		1.553343034274953323f

Camera* Camera::create() {

	return new Camera();

}

Camera* Camera::create(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar) {

	return new Camera(pos, fov, aspect, zNear, zFar);

}

Camera::Camera() {

	initialize(glm::vec3(0, 0, 0), PI * 140 / 360, 16.0 / 9.0, 0.01, 10000);

}

Camera::Camera(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar) {

	initialize(pos, fov, aspect, zNear, zFar);

}

void Camera::initialize(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar) {
	
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	setPos(pos);
	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
	m_fov = fov; m_aspect = aspect; m_znear = zNear; m_zfar = zFar;

}

void Camera::rotate(glm::vec3 amt) {

	setRot(getRot() + amt);

}

void Camera::setRot(glm::vec3 rot) {

	if (rot.x > RIGHT_ANGLE) { rot.x = RIGHT_ANGLE; }
	if (rot.x < -RIGHT_ANGLE) { rot.x = -RIGHT_ANGLE; }

	getTransform().SetRot(rot);
	m_forward = glm::vec3(getTransform().GetRotMatrix() * glm::vec4(0, 0, 1, 1));

}