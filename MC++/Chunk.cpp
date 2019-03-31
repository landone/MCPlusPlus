#include "Chunk.h"

#include <random>
#include <iostream>

unsigned int Chunk::seed = rand();

void Chunk::initialize(int x, int z) {

	initialized = true;
	this->pos = glm::vec2(x, z);

	for (int y = 0; y < HEIGHT; y++) {

		planes[y] = new Plane;

		for (int x = 0; x < WIDTH; x++) {
			for (int z = 0; z < DEPTH; z++) {

				Block& b = planes[y]->blocks[x][z];
				glm::vec3 blockPos(pos.x*WIDTH + x, y, pos.y*DEPTH + z);
				b.setPosition(blockPos);
				b.setMaterial(getBlockSeed(blockPos));

				updateVisibility(b);

			}
		}
	}

}

Chunk::Chunk() {

	//Do nothing

}

Chunk::~Chunk() {

	if (initialized) {
		for (int y = 0; y < HEIGHT; y++) {
			delete planes[y];
		}
	}

}

void Chunk::setSeed(unsigned int seed) {

	Chunk::seed = seed;

}

Block* Chunk::getBlockAt(int x, int y, int z) {

	if (x < 0 || y < 0 || z < 0 ||
		x >= WIDTH || y >= HEIGHT || z >= DEPTH) {
		return nullptr;
	}

	return &planes[y]->blocks[x][z];

}

MATERIAL Chunk::getBlockSeed(glm::vec3 pos) {

	int x = (int)pos.x;
	int y = (int)pos.y;
	int z = (int)pos.z;

	if (z >= DEPTH * 3 || z < 0 || x >= WIDTH * 3 || x < 0) {
		return AIR;
	}

	if (y > 4 || y < 0) {
		return AIR;
	}
	else if (y == 4) {
		return GRASS;
	}
	else if (y > 0) {
		return STONE;
	}
	else {
		return BEDROCK;
	}

}

void Chunk::updateVisibility(Block& b){

	unsigned int index = find(drawBlocks.begin(), drawBlocks.end(), &b) - drawBlocks.begin();

	if (b.getMaterial() == AIR) {//Don't add AIR blocks to draw vector

		if (index < drawBlocks.size()) {//Needs to be removed
			drawBlocks.erase(drawBlocks.begin() + index);
		}
		return;
	}

	glm::vec3 bPos = b.getPosition();

	MATERIAL surround[6] = {//Corresponding to block face directions
		getBlockSeed(bPos + glm::vec3(1,0,0)), getBlockSeed(bPos + glm::vec3(-1,0,0)),
		getBlockSeed(bPos + glm::vec3(0,0,1)), getBlockSeed(bPos + glm::vec3(0,0,-1)),
		getBlockSeed(bPos + glm::vec3(0,1,0)), getBlockSeed(bPos + glm::vec3(0,-1,0)),
	};

	bool visible = false;
	for (int i = 0; i < 6; i++) {

		BlockFaceDirection dir = (BlockFaceDirection)i;
		if (surround[i] == AIR) {
			visible = true;
			b.setFaceVisibility(dir, true);
		}else{
			b.setFaceVisibility(dir, false);
		}

	}

	if (visible && index == drawBlocks.size()) {//If needs to be added
		drawBlocks.push_back(&b);
	}
	else if (!visible && index < drawBlocks.size()){//If needs to be removed
		drawBlocks.erase(drawBlocks.begin() + index);
	}

}

void Chunk::setPosition(int x, int z) {

	pos = glm::vec2(x, z);

	for (int y = 0; y < HEIGHT; y++) {

		planes[y] = new Plane;

		for (int x = 0; x < WIDTH; x++) {
			for (int z = 0; z < DEPTH; z++) {

				Block& b = planes[y]->blocks[x][z];

				b.setPosition(glm::vec3(pos.x*WIDTH + x, y, pos.y*DEPTH + z));

			}
		}
	}

}

void Chunk::onDrawGeometry(GBuffer& gBuffer) {

	for (Block* b : drawBlocks) {
		b->draw(gBuffer);
	}

}