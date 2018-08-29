#pragma once

#include <string>

enum MATERIAL {
	BEDROCK,
	BRICK,
	DIRT,
	GRASS, GRASS_SIDE,
	PLANKS_OAK,
	STONE,
	STONEBRICK,
	CLAY,
	COARSE_DIRT,
	COBBLESTONE,
	COBBLESTONE_MOSSY,
	LOG_OAK,
	LOG_OAK_TOP,
	TOTAL
};

class Material {
public:

	static std::string getName(MATERIAL mat, bool fileName = false);

private:
	static std::string names[TOTAL][2];
};