#pragma once

#include "Block.h"
#include "Evt_Display.h"

#include <vector>

using namespace std;

class World;

class Chunk : public DisplayListener{
public:

	static const int WIDTH = 8, HEIGHT = 32, DEPTH = 8;

	Chunk();
	~Chunk();

	void onDrawGeometry(GBuffer& gBuffer) override;
	void initialize(int x, int z);
	void setPosition(int x, int z);

	Block* getBlockAt(int x, int y, int z);

	static void setSeed(unsigned int seed);

	//Updates existence in draw blocks vector
	void updateVisibility(Block& b);
	void updateAllVisibility(World& world);

	/*
		Determines material a block would be seeded.
		@param x,y,z Coordinates of block
		@return Supposed material.
	*/
	static MATERIAL getBlockSeed(glm::vec3 pos);

private:
	static unsigned int seed;

	bool initialized = false;

	//Position in chunk grid
	glm::vec2 pos;

	//Store blocks as planes to avoid a single huge memory grouping
	struct Plane {
		Block blocks[WIDTH][DEPTH];
	};
	Plane* planes[HEIGHT] = { nullptr };
	
	//Visible blocks to draw
	vector<Block*> drawBlocks;

};