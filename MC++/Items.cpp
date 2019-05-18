#include "Items.h"

using namespace std;

string Items::names[MAX_ITEM][2] = {
{"", "Nothing"},
{"diamond", "Diamond"},
{"stone_sword", "Stone Sword"},
{"stone_axe", "Stone Axe"},
{"stone_pickaxe", "Stone Pickaxe"},
{"stone_shovel", "Stone Shovel"},
{"stone_hoe", "Stone Hoe"},
{"stick", "Stick"}
};

string Items::getName(ITEM item, bool fileName) {

	return names[item][fileName ? 0 : 1];

}