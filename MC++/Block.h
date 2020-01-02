#pragma once

#include "Transform.h"
#include "Material.h"
#include "BlockFace.h"
#include "GBuffer.h"

#include <vector>

using namespace std;

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
	void setFaceVisibility(BlockFaceDirection dir, bool set);
	void setAllVisible();

	glm::vec3 getPosition() { return trans.GetPos(); }
	MATERIAL getMaterial() { return mat; }
	Transform& getTrans() { return trans; }
	BlockFace& getFace(BlockFaceDirection dir) { return faces[dir]; }
	bool isFaceVisible(BlockFaceDirection dir);
	bool isVisible() { return visibleFaces.size() > 0; }

private:
	Transform trans;
	MATERIAL mat = MATERIAL::AIR;
	BlockFace faces[6];
	vector<BlockFace*> visibleFaces;
};