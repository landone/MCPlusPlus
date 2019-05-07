#pragma once

#include <vector>
#include "Mesh.h"
#include "Evt_Display.h"

class MDL_Human : public DisplayListener{
public:

	MDL_Human();

	void setPos(glm::vec3);
	void setTex(Texture);
	void setHeadRotation(glm::vec3);
	void setArmRotation(glm::vec3 rot, bool right);
	void setLegRotation(glm::vec3 rot, bool right);
	void setBodyRotation(glm::vec3);

	void onDrawGeometry(GBuffer&) override;

private:

	static std::vector<Vertex> verts[6];
	static std::vector<GLuint> indices;
	static Mesh meshes[6];
	static bool initialized;

	void updatePositions();
	void updateRotations();

	glm::vec3 rots[6];
	Transform trans[6];
	Texture tex;
};