#pragma once

#include "ItemStack.h"

class Inventory {
public:

	Inventory(int size = 36);
	Inventory(std::vector<ItemStack> items);

	void empty();

	void setItem(int index, ITEM item);
	void setItem(int index, MATERIAL mat);
	void setSize(int size);

	int size() { return items.size(); }
	std::vector<ItemStack>& getItems() { return items; }
	ItemStack& getItem(int index);

private:

	std::vector<ItemStack> items;

};