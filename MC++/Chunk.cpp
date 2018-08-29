#include "Chunk.h"

#include <random>

Chunk::Chunk(int x, int z) {

	this->pos = glm::vec2(x, z);

	for (int y = 0; y < HEIGHT; y++) {

		planes[y] = new Plane;

		for (int x = 0; x < WIDTH; x++) {
			for (int z = 0; z < DEPTH; z++) {

				Block& b = planes[y]->blocks[x][z];

				//b.setMaterial((MATERIAL)(rand() % MATERIAL::TOTAL));
				b.setPosition(glm::vec3(pos.x*WIDTH + x, y, pos.y*DEPTH + z));

				if (y == 0 || y == HEIGHT - 1) {
					if (pos.x == 0 && pos.y == 0 && x == WIDTH / 2 && z == DEPTH / 2) {
						b.setMaterial(MATERIAL::BEDROCK);
					}
					else {
						b.setMaterial(MATERIAL::LOG_OAK);
					}
					drawBlocks.push_back(&b);
				}
				else if (x == 0 || x == WIDTH - 1) {
					b.setMaterial(MATERIAL::STONEBRICK);
					drawBlocks.push_back(&b);
				}
				else if (z == 0 || z == DEPTH - 1) {
					b.setMaterial(MATERIAL::COBBLESTONE);
					drawBlocks.push_back(&b);
				}
				else {
					b.setMaterial(MATERIAL::PLANKS_OAK);
				}

				if (y == 0)
					b.toggleFace(DOWN, true);
				if (y == HEIGHT - 1)
					b.toggleFace(UP, true);
				if (x == 0)
					b.toggleFace(SOUTH, true);
				if (x == WIDTH - 1)
					b.toggleFace(NORTH, true);
				if (z == 0)
					b.toggleFace(WEST, true);
				if (z == DEPTH - 1)
					b.toggleFace(EAST, true);

			}
		}
	}

}

Chunk::~Chunk() {

	for (int y = 0; y < HEIGHT; y++) {
		delete planes[y];
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