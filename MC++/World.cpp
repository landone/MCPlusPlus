#include "World.h"

World::World() {

	for (int x = 0; x < CHUNK_RENDER_DIAMETER; x++) {
		for (int z = 0; z < CHUNK_RENDER_DIAMETER; z++) {

			chunks[x][z].initialize(x, z);

		}
	}

}

Block* World::getBlockAt(int x, int y, int z) {

	x -= (int)pos.x;
	z -= (int)pos.y;

	if (y >= Chunk::HEIGHT || y < 0) {
		return nullptr;
	}

	if ((x < 0 || x >= CHUNK_RENDER_DIAMETER * Chunk::WIDTH) ||
		(z < 0 || z >= CHUNK_RENDER_DIAMETER * Chunk::DEPTH)) {
		return nullptr;
	}

	Chunk& myChunk = chunks[x / Chunk::WIDTH][z / Chunk::DEPTH];
	return myChunk.getBlockAt(x % Chunk::WIDTH, y, z % Chunk::DEPTH);

}