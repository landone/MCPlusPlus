#pragma once

#include "Block.h"
#include "Evt_Display.h"

#include <vector>

using namespace std;

class Chunk : public DisplayListener{
public:

	static const int WIDTH = 5, HEIGHT = 10, DEPTH = 5;

	Chunk();
	~Chunk();

	void onDrawGeometry(GBuffer& gBuffer);
	void initialize(int x, int z);
	void setPosition(int x, int z);

	Block* getBlockAt(int x, int y, int z);

	static void setSeed(unsigned int seed);

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

	struct Plane {
		Block blocks[WIDTH][DEPTH];
	};
	//Store blocks as planes to avoid a single huge memory grouping
	Plane* planes[HEIGHT];
	
	//Visible blocks to draw
	vector<Block*> drawBlocks;

	//TODO: Fix this function to somehow use getBlockAt() rather than getBlockSeed()
	//		Should probably honestly move this function to World
	void updateVisibility(Block& b);

};