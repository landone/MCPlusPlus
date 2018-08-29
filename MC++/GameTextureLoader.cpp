#include "GameTextureLoader.h"
#include "Block.h"

Texture* GameTextureLoader::mats = new Texture[MATERIAL::TOTAL];//Allocated for entirety of application run

void GameTextureLoader::loadMaterials() {

	for (int i = 0; i < MATERIAL::TOTAL; i++) {
		mats[i] = Texture();
		mats[i].Load("./res/textures/materials/" + Material::getName((MATERIAL)i, true).append(".png"));
	}

}