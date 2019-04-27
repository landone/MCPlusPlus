#include "GameTextureLoader.h"
#include "Block.h"

Texture* GameTextureLoader::mats = new Texture[MATERIAL::MAT_TOTAL];//Allocated for entirety of application run

void GameTextureLoader::loadMaterials() {
	//Start at 1 to avoid AIR
	for (int i = 1; i < MATERIAL::MAT_TOTAL; i++) {
		mats[i] = Texture();
		mats[i].Load("./res/textures/materials/" + Material::getName((MATERIAL)i, true).append(".png"));
	}

}