#pragma once

#include "Texture.h"
#include "Material.h"
#include "Text.h"
#include "GUI_Components.h"

class GameTextureLoader {
public:

	static void loadMaterials();
	static void loadFonts();
	static void loadGUI();

	static Texture& getMaterial(MATERIAL m) {
		return mats[(int)m];
	}

	static Texture& getFont(FONT f) {
		return fonts[f];
	}

	static Texture& getGUI(GUI_Component g) {
		return gui[g];
	}

private:
	static Texture mats[MATERIAL::MAX_MAT];
	static Texture fonts[FONT::MAX_FONT];
	static Texture gui[GUI_Component::MAX_GUI];

	static Texture crop(BasicShader& shader, Transform& trans, Texture& base, glm::vec2 dim, Mesh& quad,
		glm::vec2 bottomLeft, glm::vec2 topRight);

};