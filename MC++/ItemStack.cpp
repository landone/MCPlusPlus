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

void ItemStack::setType(ITEM i) {

	trans_gui.SetScale(glm::vec3(1.2, 1.2, 1.2));

	is_block = false;
	item_type = i;
	setName(Items::getName(i));
	mesh = &GameAssetLoader::getItemMesh(i);
	tex = &GameAssetLoader::getItemTex(i);

}

void ItemStack::setMaterial(MATERIAL m) {

	trans_gui.SetScale(glm::vec3(0.4, 0.4, 0.4));

	is_block = true;
	mat_type = m;
	setName(Material::getName(m));
	block.setMaterial(m);
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