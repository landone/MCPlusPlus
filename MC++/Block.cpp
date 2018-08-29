#include "Block.h"
#include "Mesh.h"

Block::Block(MATERIAL mat, glm::vec3 pos) : faces{ BlockFace(BlockFaceDirection::NORTH, mat), BlockFace(BlockFaceDirection::SOUTH, mat),
	BlockFace(BlockFaceDirection::EAST, mat), BlockFace(BlockFaceDirection::WEST, mat), BlockFace(BlockFaceDirection::UP, mat), BlockFace(BlockFaceDirection::DOWN, mat) } {

	trans.SetPos(pos);

}

void Block::draw(GBuffer& gbuf) {

	gbuf.setTransMat(trans.GetMatrix());
	gbuf.setRotMat(trans.GetRotMatrix());
	for (int i = 0; i < 6; i++) {
		faces[i].draw();
	}

}

void Block::setMaterial(MATERIAL mat) {
	for (int i = 0; i < 6; i++) {
		faces[i].setMaterial(mat);
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

void Block::toggleFace(BlockFaceDirection dir, bool set) {
	
	faces[dir].toggle(set);

}

bool Block::isFaceVisible(BlockFaceDirection dir) {

	return faces[dir].isVisible();

}