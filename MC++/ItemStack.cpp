#include "ItemStack.h"

ItemStack::ItemStack(ITEM i, int amt) {

	trans_gui.SetPos(glm::vec3(-0.64, -0.55, 0.6));
	trans_gui.SetRot(glm::vec3(3.1415f / 3.0f, -3.1415f / 3.0f, -3.1415f / 3.0f));

	setType(i);
	setAmount(amt);

}

ItemStack::ItemStack(MATERIAL m, int amt) {


	trans_gui.SetPos(glm::vec3(-0.64, -0.55, 0.6));
	trans_gui.SetRot(glm::vec3(3.1415f / 3.0f, -3.1415f / 3.0f, -3.1415f / 3.0f));

	setMaterial(m);
	setAmount(amt);

}

Texture& ItemStack::getTexture() {

	if (isBlock()) {
		return GameAssetLoader::getMaterial(mat_type);
	}
	return GameAssetLoader::getItemTex(item_type);

}

void ItemStack::setType(ITEM i) {

	trans_gui.SetScale(glm::vec3(1.2, 1.2, 1.2));

	is_block = false;
	item_type = i;
	setName(Items::getName(i));
	mesh = &GameAssetLoader::getItemMesh(i);
	tex = &GameAssetLoader::getItemTex(i);

}

void ItemStack::setMaterial(MATERIAL m) {

	trans_gui.SetScale(glm::vec3(0.4f, 0.4f, 0.4f));//Default block gui scale

	is_block = true;
	mat_type = m;
	setName(Material::getName(m));
	block.setMaterial(m);
	trans.SetScale(glm::vec3(0.3f, 0.3f, 0.3f));//Default block item scale
	block.getTrans() = gui ? trans_gui : trans;
	block.setAllVisible();

}

void ItemStack::setName(std::string str) {

	name = str;

}

void ItemStack::setAmount(int amt) {

	amount = amt;

}

void ItemStack::setPhysical(bool toggle) {

	isWorld = toggle;

}

void ItemStack::setGUI(bool toggle) {
	
	gui = toggle;
	if (is_block) {
		block.getTrans() = gui ? trans_gui : trans;
	}

}

Transform& ItemStack::getTrans() {

	if (is_block) {
		return block.getTrans();
	}

	return gui ? trans_gui : trans;

}

bool ItemStack::isNothing() {

	if (isBlock()) {
		return getMaterial() == MATERIAL::AIR;
	}

	return getType() == ITEM::NOTHING;

}

void ItemStack::onDrawGeometry(GBuffer& gBuf) {

	if (isWorld && !gui) {
		if (is_block) {
			block.draw(gBuf);
		}
		else {
			gBuf.setTransMat(trans.GetMatrix());
			gBuf.setRotMat(trans.GetRotMatrix());
			tex->bind();
			mesh->draw();
		}
	}

}

void ItemStack::onDraw3DGUI(GBuffer& gBuf) {

	if (isWorld && gui) {
		if (is_block) {
			block.draw(gBuf);
		}
		else {
			gBuf.setTransMat(trans_gui.GetMatrix());
			gBuf.setRotMat(trans_gui.GetRotMatrix());
			tex->bind();
			mesh->draw();
		}
	}

}