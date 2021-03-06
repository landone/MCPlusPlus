#include "Material.h"

using namespace std;

string Material::names[MAX_MAT][2] = {
	{"air", "Air"},
	{ "bedrock", "Bedrock" },
	{ "brick", "Brick" },
	{ "dirt", "Dirt" },
	{ "grass", "Grass" },
	{ "grass_side", "Grass Side" },
	{ "planks_oak", "Oak Planks" },
	{ "stone", "Stone" },
	{ "stonebrick", "StoneBrick" },
	{ "clay", "Clay" },
	{ "coarse_dirt", "Coarse Dirt" },
	{ "cobblestone", "Cobblestone" },
	{ "cobblestone_mossy", "Mossy Cobblestone" },
	{ "log_oak", "Oak Log" },
	{ "log_oak_top", "Oak Log Top" },
	{"iron_ore", "Iron Ore" },
	{"lapis_ore", "Lapis Ore" },
	{"diamond_ore", "Diamond Ore" },
	{"coal_ore", "Coal Ore" }
};

std::string Material::getName(MATERIAL mat, bool fileName) {

	return names[(int)mat][fileName ? 0 : 1];

}