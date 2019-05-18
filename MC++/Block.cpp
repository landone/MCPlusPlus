#include "Block.h"
#include "Mesh.h"

#include <algorithm>

Block::Block(MATERIAL mat, glm::vec3 pos) : faces{ BlockFace(BlockFaceDirection::NORTH, mat), BlockFace(BlockFaceDirection::SOUTH, mat),
	BlockFace(BlockFaceDirection::EAST, mat), BlockFace(BlockFaceDirection::WEST, mat), BlockFace(BlockFaceDirection::UP, mat), BlockFace(BlockFaceDirection::DOWN, mat) } {

	trans.SetPos(pos);

}

void Block::draw(GBuffer& gbuf) {

	gbuf.setTransMat(trans.GetMatrix());
	gbuf.setRotMat(trans.GetRotMatrix());
	for (BlockFace* f : visibleFaces) {
		f->draw();
	}

}

void Block::setMaterial(MATERIAL mat) {
	this->mat = mat;
	if (mat == GRASS) {
		faces[UP].setMaterial(GRASS);
		faces[DOWN].setMaterial(DIRT);
		faces[NORTH].setMaterial(GRASS_SIDE);
		faces[SOUTH].setMaterial(GRASS_SIDE);
		faces[WEST].setMaterial(GRASS_SIDE);
		faces[EAST].setMaterial(GRASS_SIDE);
	}
	else if (mat == LOG_OAK) {
		faces[UP].setMaterial(LOG_OAK_TOP);
		faces[DOWN].setMaterial(LOG_OAK_TOP);
		faces[NORTH].setMaterial(LOG_OAK);
		faces[SOUTH].setMaterial(LOG_OAK);
		faces[WEST].setMaterial(LOG_OAK);
		faces[EAST].setMaterial(LOG_OAK);
	}
	else {
		for (int i = 0; i < 6; i++) {
			faces[i].setMaterial(mat);
		}
	}
}

void Block::setPosition(glm::vec3 pos) {
	trans.SetPos(pos);
}

void Block::move(glm::vec3 amt) {
	trans.SetPos(trans.GetPos() + amt);
}

void Block::setRotation(glm::vec3 rot) {
	trans.SetRot(rot);
}

void Block::setFaceVisibility(BlockFaceDirection dir, bool set) {

	BlockFace& face = faces[dir];

	unsigned int index = find(visibleFaces.begin(), visibleFaces.end(), &face) - visibleFaces.begin();
	if (index == visibleFaces.size() && set) {//Not found and need to add
		visibleFaces.push_back(&face);
	}
	else if (index < visibleFaces.size() && !set) {//Found and need to remove
		visibleFaces.erase(visibleFaces.begin() + index);
	}

}

bool Block::isFaceVisible(BlockFaceDirection dir) {

	BlockFace& face = faces[dir];

	int index = find(visibleFaces.begin(), visibleFaces.end(), &face) - visibleFaces.begin();
	return index != visibleFaces.size();

}

void Block::setAllVisible() {

	for (int i = 0; i < 6; i++) {
		setFaceVisibility((BlockFaceDirection)i, true);
	}

}