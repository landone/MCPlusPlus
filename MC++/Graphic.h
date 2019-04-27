#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Shader.h"
#include "Evt_Display.h"

class Graphic : public DisplayListener {
public:

	Graphic(Texture& tex);

	void onDrawGUI(GBuffer& gBuffer) override;

	Transform trans;

private:

	Mesh mesh;
	Texture tex;

};