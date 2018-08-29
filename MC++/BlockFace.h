#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "BlockFaceDirection.h"
#include "Material.h"

class BlockFace {
public:

	BlockFace(BlockFaceDirection dir, MATERIAL mat);

	void setMaterial(MATERIAL t);
	void toggle(bool set) { visible = set; }
	void draw();

	bool isVisible() { return visible; }

private:
	Texture* myTex = nullptr;
	Mesh* myMesh = nullptr;
	bool visible = false;

	static Mesh** meshes;
	static std::vector<Vertex> verts[6];
	static std::vector<GLuint> indices;
	static bool meshInit;

};