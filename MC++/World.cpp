#include "World.h"
#include <iostream>

World::World() {
	itemDrops.reserve(5);
	for (int x = 0; x < CHUNK_RENDER_DIAMETER; x++) {
		for (int z = 0; z < CHUNK_RENDER_DIAMETER; z++) {

			chunks[x][z].initialize(x, z);

		}
	}

	for (int x = 0; x < CHUNK_RENDER_DIAMETER; x++) {
		for (int z = 0; z < CHUNK_RENDER_DIAMETER; z++) {

			chunks[x][z].updateAllVisibility(*this);

		}
	}

}

void World::spawnItem(MATERIAL m, glm::vec3 pos) {
	
	itemDrops.push_back(new ItemDrop());
	ItemStack& stack = itemDrops[itemDrops.size() - 1]->s;
	stack.setMaterial(m);
	stack.setPhysical(true);
	stack.setGUI(false);
	stack.getTrans().SetScale(glm::vec3(0.4, 0.4, 0.4));
	stack.getTrans().SetPos(pos + glm::vec3(0.5, 0.3, 0.5));

}

void World::onFrame(double delta) {

	for (unsigned int i = 0; i < itemDrops.size(); i++) {
		itemDrops[i]->s.getTrans().rotate(glm::vec3(0, 0.05f, 0));
	}

}

Block* World::getBlockAt(int x, int y, int z) {

	Chunk* myChunk = getChunkAt(x, y, z);

	if (myChunk == nullptr) {
		return nullptr;
	}

	x -= (int)w_pos.x;
	z -= (int)w_pos.y;

	return myChunk->getBlockAt(x % Chunk::WIDTH, y, z % Chunk::DEPTH);

}

Chunk* World::getChunkAt(int x, int y, int z) {

	x -= (int)w_pos.x;
	z -= (int)w_pos.y;

	if (y >= Chunk::HEIGHT || y < 0) {
		return nullptr;
	}

	if ((x < 0 || x >= CHUNK_RENDER_DIAMETER * Chunk::WIDTH) ||
		(z < 0 || z >= CHUNK_RENDER_DIAMETER * Chunk::DEPTH)) {
		return nullptr;
	}

	return &chunks[x / Chunk::WIDTH][z / Chunk::DEPTH];

}

void World::updateVisibility(Block* block) {

	Block& b = *block;
	bool amAir = b.getMaterial() == AIR;
	glm::vec3 bPos = b.getPosition();

	Block* surround[6] = {//Corresponding to block face directions
		getBlockAt(bPos + glm::vec3(1,0,0)), getBlockAt(bPos + glm::vec3(-1,0,0)),
		getBlockAt(bPos + glm::vec3(0,0,1)), getBlockAt(bPos + glm::vec3(0,0,-1)),
		getBlockAt(bPos + glm::vec3(0,1,0)), getBlockAt(bPos + glm::vec3(0,-1,0)),
	};

	for (int i = 0; i < 6; i++) { //Set shared-face visibilities for all blocks
		BlockFaceDirection dir = (BlockFaceDirection)i;
		if (surround[i] == nullptr) {
			b.setFaceVisibility(dir, !amAir);
			continue;
		}

		BlockFaceDirection opp = (BlockFaceDirection)(i % 2 == 0 ? i + 1 : i - 1);
		bool youAir = surround[i]->getMaterial() == AIR;

		b.setFaceVisibility(dir, !amAir && youAir);
		surround[i]->setFaceVisibility(opp, amAir && !youAir);
		getChunkAt(surround[i]->getPosition())->updateVisibility(*surround[i]);

	}

	getChunkAt(bPos)->updateVisibility(b);

}

Block* World::traceRay(glm::vec3 pos, glm::vec3 dir, float reach, bool prev, glm::vec3* result, glm::vec3* axis) {
	glm::vec3 origin = pos;
	Block* prevBlock = nullptr;
	glm::vec3 normal(0,0,0);
	while(glm::distance(origin, pos) <= reach) {
		Block* block = getBlockAt(pos);
		if (block && block->getMaterial() != AIR) {
			if (result) {
				(*result) = pos;
			}
			if (axis) {
				(*axis) = normal;
			}
			return prev ? prevBlock : block;
		}
		prevBlock = block;
		float dist[3];
		bool approx[3];
		dist[0] = floorf(pos[0]);
		approx[0] = pos[0] - dist[0] < 0.00005f;
		dist[0] = dir[0] > 0 ? dist[0] + 1.0f : (approx[0] ? dist[0] - 1.0f : dist[0]);
		dist[0] -= pos[0];
		dist[1] = floorf(pos[1]);
		approx[1] = pos[1] - dist[1] < 0.00005f;
		dist[1] = dir[1] > 0 ? dist[1] + 1.0f : (approx[1] ? dist[1] - 1.0f : dist[1]);
		dist[1] -= pos[1];
		dist[2] = floorf(pos[2]);
		approx[2] = pos[2] - dist[2] < 0.00005f;
		dist[2] = dir[2] > 0 ? dist[2] + 1.0f : (approx[2] ? dist[2] - 1.0f : dist[2]);
		dist[2] -= pos[2];
		float ratios[3];
		ratios[0] = dir[0] == 0.0f ? INFINITY : dist[0] / dir[0];
		ratios[1] = dir[1] == 0.0f ? INFINITY : dist[1] / dir[1];
		ratios[2] = dir[2] == 0.0f ? INFINITY : dist[2] / dir[2];
		if (ratios[0] < ratios[1] && ratios[0] < ratios[2]) {
			pos[0] += dist[0];
			pos[1] += ratios[0] * dir[1];
			pos[2] += ratios[0] * dir[2];
			if (dir[0] <= 0 && !approx[0]) {
				pos[0] -= 0.0001f;
			}
			normal = glm::vec3(dir[0] > 0.0f ? -1.0f : 1.0f, 0, 0);
		}
		else if (ratios[1] < ratios[2]) {
			pos[1] += dist[1];
			pos[0] += ratios[1] * dir[0];
			pos[2] += ratios[1] * dir[2];
			if (dir[1] <= 0 && !approx[1]) {
				pos[1] -= 0.0001f;
			}
			normal = glm::vec3(0, dir[1] > 0.0f ? -1.0f : 1.0f, 0);
		}
		else {
			pos[2] += dist[2];
			pos[1] += ratios[2] * dir[1];
			pos[0] += ratios[2] * dir[0];
			if (dir[2] < 0 && !approx[2]) {
				pos[2] -= 0.0001f;
			}
			normal = glm::vec3(0, 0, dir[2] > 0.0f ? -1.0f : 1.0f);
		}
	}

	return nullptr;

}