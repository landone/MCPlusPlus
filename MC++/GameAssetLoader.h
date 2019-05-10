#pragma once

#include "Texture.h"
#include "Material.h"
#include "Text.h"
#include "Entities.h"
#include "Items.h"
#include "GUI_Components.h"

class GameAssetLoader {
public:

	static void loadAll();

	static void loadMaterials();
	static void loadFonts();
	static void loadGUI();
	static void loadEntities();
	static void loadItems();

	static Texture& getMaterial(MATERIAL m) {
		return mats[(int)m];
	}

	static Texture& getFont(FONT f) {
		return fonts[f];
	}

	static Texture& getGUI(GUI_Component g) {
		return gui[g];
	}

	static Texture& getEntity(ENTITIES e) {
		return ents[e];
	}

	static Texture& getItemTex(ITEM i) {
		return items[i];
	}

	static Mesh& getItemMesh(ITEM i) {
		return items_mesh[i];
	}

private:
	static Texture mats[MATERIAL::MAX_MAT];
	static Texture fonts[FONT::MAX_FONT];
	static Texture gui[GUI_Component::MAX_GUI];
	static Texture ents[ENTITIES::MAX_ENT];

	static Texture items[ITEM::MAX_ITEM];
	static Mesh items_mesh[ITEM::MAX_ITEM];

	static Texture crop(BasicShader& shader, Transform& trans, Texture& base, glm::vec2 dim, Mesh& quad,
		glm::vec2 bottomLeft, glm::vec2 topRight);

};