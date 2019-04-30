#pragma once

enum MATERIAL {
	AIR = 0,
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
	IRON_ORE,
	LAPIS_ORE,
	DIAMOND_ORE,
	COAL_ORE,
	MAX_MAT
};

#include <string>

class Material {
public:

	static std::string getName(MATERIAL mat, bool fileName = false);

private:
	static std::string names[MAX_MAT][2];
};