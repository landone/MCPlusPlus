#pragma once

#include "Texture.h"
#include "Material.h"

class GameTextureLoader {
public:

	static void loadMaterials();

	static Texture& getMaterial(MATERIAL m) {
		return mats[(int)m];
	}

private:
	static Texture* mats;
};