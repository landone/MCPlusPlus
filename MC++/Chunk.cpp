#include "Chunk.h"

#include <random>

unsigned int Chunk::seed = rand();

Chunk::Chunk(int x, int z) {

	this->pos = glm::vec2(x, z);

	for (int y = 0; y < HEIGHT; y++) {

		planes[y] = new Plane;

		for (int x = 0; x < WIDTH; x++) {
			for (int z = 0; z < DEPTH; z++) {

				Block& b = planes[y]->blocks[x][z];
				b.setPosition(glm::vec3(pos.x*WIDTH + x, y, pos.y*DEPTH + z));

				glm::vec3 pos = b.getPosition();
				MATERIAL myMat = getBlockSeed(pos);
				b.setMaterial(myMat);
				if (myMat == AIR) {//Don't add AIR blocks to draw vector
					continue;
				}

				MATERIAL surround[6] = {//Corresponding to block face directions
					getBlockSeed(pos + glm::vec3(1,0,0)), getBlockSeed(pos + glm::vec3(-1,0,0)),
					getBlockSeed(pos + glm::vec3(0,0,1)), getBlockSeed(pos + glm::vec3(0,0,-1)),
					getBlockSeed(pos + glm::vec3(0,1,0)), getBlockSeed(pos + glm::vec3(0,-1,0)),
				};

				bool visible = false;
				for (int i = 0; i < 6; i++) {
					if (surround[i] == AIR) {
						visible = true;
						b.setFaceVisibility((BlockFaceDirection)i, true);
					}
				}
				
				if (visible) {
					drawBlocks.push_back(&b);
				}

			}
		}
	}

}

Chunk::~Chunk() {

	for (int y = 0; y < HEIGHT; y++) {
		delete planes[y];
	}

}

void Chunk::setSeed(unsigned int seed) {

	Chunk::seed = seed;

}

MATERIAL Chunk::getBlockSeed(glm::vec3 pos) {

	int x = (int)pos.x;
	int y = (int)pos.y;
	int z = (int)pos.z;

	if (z >= DEPTH * 2 || z < DEPTH * -1 || x >= WIDTH * 2 || x < WIDTH * -1) {
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