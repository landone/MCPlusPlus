#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Entity.h"

#ifndef PI
#define PI		3.1415926535f
#endif

class Camera : public Entity {
public:

	static Camera* create();
	static Camera* create(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar);

	void changeAspect(double W, double H) {
		m_aspect = (W / H);
		m_perspective = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
	}

	void setFOV(double fov) {
		m_fov = fov;
		m_perspective = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
	}

	double getFOV() { return m_fov; }

	glm::vec3& getForward() { return m_forward; }
	glm::vec3& getUp() { return m_up; }

	void rotate(glm::vec3 amt) override;
	void setRot(glm::vec3 amt) override;

	glm::mat4 getViewMatrix() {
		return m_perspective * glm::lookAt(getPos(), getPos() + m_forward, m_up);
	}

protected:

	Camera(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar);
	Camera();

private:

	void initialize(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar);

	glm::mat4 m_perspective;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	double m_fov, m_aspect, m_znear, m_zfar;
};