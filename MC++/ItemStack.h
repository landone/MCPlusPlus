#pragma once

#include "GameAssetLoader.h"
#include "Items.h"
#include "Block.h"

class ItemStack : public DisplayListener{
public:

	ItemStack(ITEM = ITEM::NOTHING, int = 1);
	ItemStack(MATERIAL, int = 1);
	~ItemStack();

	void setType(ITEM);
	void setMaterial(MATERIAL);
	void setName(std::string);
	void setAmount(int);
	void setPhysical(bool);
	void setGUI(bool);

	ITEM getType() { return item_type; }
	MATERIAL getMaterial() { return mat_type; }
	std::string getName() { return name; }
	int getAmount() { return amount; }
	bool isPhysical() { return isWorld; }
	bool isGUI() { return gui; }
	bool isBlock() { return is_block; }
	Transform& getTrans();

	void onDrawGeometry(GBuffer&) override;
	void onDraw3DGUI(GBuffer&) override;

private:

	ITEM item_type = ITEM::NOTHING;
	MATERIAL mat_type = MATERIAL::AIR;
	int amount = 1;
	bool isWorld = false;
	bool gui = false;
	bool is_block = false;
	Block* block = nullptr;
	std::string name;

	Transform trans;
	Transform trans_gui;
	Mesh mesh;
	Texture tex;

};