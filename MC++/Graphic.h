#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Shader.h"
#include "Evt_Display.h"

class Graphic : public DisplayListener {
public:

	Graphic();
	Graphic(Texture& tex);

	void setTexture(Texture& tex);
	void onDrawGUI(GBuffer& gBuffer) override;

	static Mesh* getQuadMesh();

	Transform trans;

private:

	static Mesh* mesh;
	Texture tex;

};