#pragma once

#include "Chunk.h"

class World {
public:

	World();

	Block* getBlockAt(glm::vec3 pos) { return getBlockAt(floor(pos.x), floor(pos.y), floor(pos.z)); }
	Block* getBlockAt(int x, int y, int z);
	Chunk* getChunkAt(glm::vec3 pos) { return getChunkAt(floor(pos.x), floor(pos.y), floor(pos.z)); }
	Chunk* getChunkAt(int x, int y, int z);
	void updateVisibility(Block* block);

	Block* traceRay(glm::vec3 pos, glm::vec3 dir, float reach, bool prev = false, glm::vec3* result = nullptr);

private:
	static const int CHUNK_RENDER_RADIUS = 2;
	static const int CHUNK_RENDER_DIAMETER = CHUNK_RENDER_RADIUS * 2 - 1;

	//Array of visible chunks
	Chunk chunks[CHUNK_RENDER_DIAMETER][CHUNK_RENDER_DIAMETER];

	//Position in world of first chunk (x,z)
	glm::vec2 w_pos;

};