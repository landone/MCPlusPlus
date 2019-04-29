#pragma once

#include "Texture.h"
#include "Material.h"

class GameTextureLoader {
public:

	static void loadMaterials();
	static void loadFonts();

	static Texture& getMaterial(MATERIAL m) {
		return mats[(int)m];
	}

	static Texture& getFont() {
		return font;
	}

private:
	static Texture* mats;
	static Texture font;
};