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

	int count() { return itemCount; }
	int size() { return items.size(); }
	const std::vector<ItemStack>& getItems() { return items; }
	ItemStack& getItem(int index);
	bool isEmpty() { return itemCount == 0; }
	bool isFull() { return itemCount == items.size(); }

private:

	void updateCount();
	int itemCount = 0;
	std::vector<ItemStack> items;

};