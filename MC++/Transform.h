#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "glm\gtx\transform.hpp"

class Transform {
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	inline glm::mat4 GetMatrix() const {
		return matrix;
	}

	inline glm::mat4& GetRotMatrix() {
		return rotMatr;
	}

	inline void CalcMatrix() {
		matrix = posMatr * rotMatr * scaleMatr;
	}

	inline glm::vec3 GetPos() { return m_pos; }
	inline glm::vec3 GetRot() { return m_rot; }
	inline glm::vec3 GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; posMatr = glm::translate(m_pos); CalcMatrix(); }
	inline void SetRot(const glm::vec3& pos) {
		m_rot = pos;
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		rotMatr = rotZMatrix * rotYMatrix * rotXMatrix;
		CalcMatrix();
	}

	inline void SetScale(const glm::vec3& pos) { m_scale = pos; scaleMatr = glm::scale(m_scale); CalcMatrix(); }
protected:
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	glm::mat4 matrix, posMatr, rotMatr, scaleMatr;
};