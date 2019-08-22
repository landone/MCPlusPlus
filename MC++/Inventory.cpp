#include "Inventory.h"

Inventory::Inventory(int size) {

	setSize(size);

}

Inventory::Inventory(std::vector<ItemStack> items) {

	this->items = items;
	updateCount();

}

void Inventory::updateCount() {
	for (unsigned int i = 0; i < items.size(); i++) {
		if (!items[i].isNothing()) {
			itemCount++;
		}
	}
}

ItemStack& Inventory::getItem(int index) {

	if (index < 0 || index >= (int)items.size()) {
		index = 0;
	}

	return items[index];

}

void Inventory::setItem(int index, ITEM item) {

	if (index < 0 || index >= (int)items.size()) {
		return;
	}
	if (items[index].isNothing()) {
		if (item != ITEM::NOTHING) {
			itemCount++;
		}
	}
	else if (item == ITEM::NOTHING) {
		itemCount--;
	}
	items[index].setType(item);

}

void Inventory::setItem(int index, MATERIAL mat) {

	if (index < 0 || index >= (int)items.size()) {
		return;
	}
	if (items[index].isNothing()) {
		if (mat != MATERIAL::AIR) {
			itemCount++;
		}
	}
	else if (mat == MATERIAL::AIR) {
		itemCount--;
	}
	items[index].setMaterial(mat);

}

void Inventory::setSize(int size) {

	if (size < 0) {
		size = 0;
	}

	items.resize(size);
	updateCount();

}

void Inventory::empty() {

	ItemStack blank;

	for (unsigned int i = 0; i < items.size(); i++) {
		items[i] = blank;
	}

}