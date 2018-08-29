#pragma once

#include "Block.h"
#include "Evt_Display.h"

#include <vector>

using namespace std;

class Chunk : public DisplayListener{
public:

	Chunk() : Chunk(0, 0) {}
	Chunk(int x, int z);
	~Chunk();

	void onDrawGeometry(GBuffer& gBuffer);

	void setPosition(int x, int z);

	static void setSeed(unsigned int seed);

	/*
		Determines material a block would be seeded.
		@param x,y,z Coordinates of block
		@return Supposed material.
	*/
	static MATERIAL getBlockSeed(glm::vec3 pos);

private:
	static const int WIDTH = 5, HEIGHT = 5, DEPTH = 5;
	static unsigned int seed;

	glm::vec2 pos;//Position relative to chunks, not world

	struct Plane {
		Block blocks[WIDTH][DEPTH];
	};
	Plane* planes[HEIGHT];//Store blocks as planes to avoid a single huge memory grouping
	
	vector<Block*> drawBlocks;//Visible blocks to draw

};