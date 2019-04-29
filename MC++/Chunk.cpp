#include "Chunk.h"
#include "World.h"

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

			}
		}
	}

}

void Chunk::updateAllVisibility(World& world) {

	for (int y = 0; y < HEIGHT; y++) {
		Plane& plane = *planes[y];
		for (int x = 0; x < WIDTH; x++) {
			for (int z = 0; z < DEPTH; z++) {
				world.updateVisibility(&(plane.blocks[x][z]));
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

	if (z >= DEPTH * 3 || z < 0 || x >= WIDTH * 3 || x < 0) { //Change hard-coded chunk constants to world variables
		return AIR;
	}

	if (y > 24 || y < 0) {
		return AIR;
	}
	else if (y == 24) {
		return GRASS;
	}
	else if (y > 0) {
		switch ((int)(abs(sin(x)) * 75 + abs(cos(z)) * 64 + abs(sin(y)) * 64 + abs(cos(y)) * 150) % 230) {
		case 0:
			return DIAMOND_ORE;
		case 1:
			return COAL_ORE;
		case 2:
			return LAPIS_ORE;
		case 3:
			return IRON_ORE;
		default:
			return STONE;
		}
	}
	else {
		return BEDROCK;
	}

}

void Chunk::updateVisibility(Block& b){

	unsigned int index = find(drawBlocks.begin(), drawBlocks.end(), &b) - drawBlocks.begin();
	if (b.isVisible()) {
		if (index == drawBlocks.size()) {//Add if not in
			drawBlocks.push_back(&b);
		}
	} else {
		if (index < drawBlocks.size()) {//Remove if in
			drawBlocks.erase(drawBlocks.begin() + index);
		}
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