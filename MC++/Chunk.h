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

private:
	static const int WIDTH = 5, HEIGHT = 5, DEPTH = 5;

	glm::vec2 pos;

	struct Plane {
		Block blocks[WIDTH][DEPTH];
	};

	Plane* planes[HEIGHT];//Store blocks as planes to avoid huge memory grouping
	vector<Block*> drawBlocks;//TODO: Replace with blockfaces rather than blocks
								//		to avoid furthermore iterations

};