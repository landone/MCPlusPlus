#pragma once

#include "Chunk.h"

class World {
public:

	World();

	Block* getBlockAt(int x, int y, int z);

private:
	static const int CHUNK_RENDER_RADIUS = 2;
	static const int CHUNK_RENDER_DIAMETER = CHUNK_RENDER_RADIUS * 2 - 1;

	//Array of visible chunks
	Chunk chunks[CHUNK_RENDER_DIAMETER][CHUNK_RENDER_DIAMETER];

	//Position in world of first chunk (x,z)
	glm::vec2 pos;

};