#include "Inventory.h"

Inventory::Inventory(int size) {

	setSize(size);

}

Inventory::Inventory(std::vector<ItemStack> items) {

	this->items = items;

}

ItemStack& Inventory::getItem(int index) {

	if (index < 0 || index >= items.size()) {
		index = 0;
	}

	return items[index];

}

void Inventory::setItem(int index, ITEM item) {

	if (index < 0 || index >= items.size()) {
		return;
	}

	items[index].setType(item);

}

void Inventory::setItem(int index, MATERIAL mat) {

	if (index < 0 || index >= items.size()) {
		return;
	}

	items[index].setMaterial(mat);

}

void Inventory::setSize(int size) {

	if (size < 0) {
		size = 0;
	}

	items.resize(size);

}

void Inventory::empty() {

	ItemStack blank;

	for (int i = 0; i < items.size(); i++) {
		items[i] = blank;
	}

}