#pragma once

enum ITEM {
	NOTHING = 0,
	DIAMOND,
	STONE_SWORD,
	STONE_AXE,
	STONE_PICKAXE,
	STONE_SHOVEL,
	STONE_HOE,
	STICK,
	MAX_ITEM
};

#include <string>

class Items {
public:

	static std::string getName(ITEM item, bool fileName = false);

private:
	static std::string names[MAX_ITEM][2];
};