#pragma once

enum ITEM {
	NOTHING = 0,
	DIAMOND,
	MAX_ITEM
};

#include <string>

class Items {
public:

	static std::string getName(ITEM item, bool fileName = false);

private:
	static std::string names[MAX_ITEM][2];
};