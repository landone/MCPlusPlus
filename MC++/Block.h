#pragma once

#include "Transform.h"
#include "Material.h"
#include "BlockFace.h"
#include "GBuffer.h"

#include <string>

class Block {
public:

	Block() : Block((MATERIAL)0, glm::vec3(0)) {}
	Block(MATERIAL m) : Block(m, glm::vec3(0)) {}
	Block(MATERIAL, glm::vec3);

	void draw(GBuffer& gbuf);

	void setPosition(glm::vec3 pos);
	void move(glm::vec3 amt);
	void setRotation(glm::vec3 rot);
	void setMaterial(MATERIAL mat);
	void toggleFace(BlockFaceDirection, bool);

	glm::vec3 getPosition() { return trans.GetPos(); }
	MATERIAL getMaterial() { return mat; }
	bool isFaceVisible(BlockFaceDirection);

private:
	Transform trans;
	MATERIAL mat;
	BlockFace faces[6];
};