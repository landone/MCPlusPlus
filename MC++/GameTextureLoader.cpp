#include "GameTextureLoader.h"
#include "Block.h"

Texture GameTextureLoader::mats[MATERIAL::MAX_MAT];//Allocated for entirety of application run
Texture GameTextureLoader::fonts[FONT::MAX_FONT];
Texture GameTextureLoader::gui[GUI_Component::MAX_GUI];
Texture GameTextureLoader::ents[ENTITIES::MAX_ENT];

static const std::string TEXTURE_PATH = "./res/texture/";

void GameTextureLoader::loadMaterials() {
	//Start at 1 to avoid AIR
	for (int i = 1; i < MATERIAL::MAX_MAT; i++) {
		mats[i].Load(TEXTURE_PATH + "material/" + Material::getName((MATERIAL)i, true) + ".png");
	}

}

void GameTextureLoader::loadFonts() {

	fonts[ASCII].Load(TEXTURE_PATH + "font/ascii.png");

}

void GameTextureLoader::loadGUI() {

	BasicShader& shader = *BasicShader::getGlobal();
	shader.setTint(glm::vec3(1, 1, 1));
	Transform trans;
	trans.SetPos(glm::vec3(-1, -1, 0));//Bottom left corner
	shader.setTransMat(trans.GetMatrix());
	Mesh& mesh = *Graphic::getQuadMesh();
	GLint dimensions[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dimensions);
	glm::vec2 dimf(dimensions[2], dimensions[3]);

	Texture icons(TEXTURE_PATH + "gui/icons.png");
	Texture widgets(TEXTURE_PATH + "gui/widgets.png");

	//Texture vectors are in pixels with topLeft = (0,0)
	gui[GUI_CROSSHAIR] = crop(shader, trans, icons, dimf, mesh, glm::vec2(0,16), glm::vec2(16,0));
	gui[GUI_MENU_BAR] = crop(shader, trans, widgets, dimf, mesh, glm::vec2(1, 85), glm::vec2(198, 67));
	gui[GUI_MENU_BAR_HOVER] = crop(shader, trans, widgets, dimf, mesh, glm::vec2(1, 105), glm::vec2(199, 87));
	gui[GUI_MENU_BAR_DOWN] = crop(shader, trans, widgets, dimf, mesh, glm::vec2(1, 65), glm::vec2(199, 47));
	gui[GUI_HOTBAR] = crop(shader, trans, widgets, dimf, mesh, glm::vec2(1, 1), glm::vec2(181, 21));
	gui[GUI_HOTBAR_SELECT] = crop(shader, trans, widgets, dimf, mesh, glm::vec2(1, 23), glm::vec2(23, 45));
	gui[GUI_HEART] = crop(shader, trans, icons, dimf, mesh, glm::vec2(52, 8), glm::vec2(60, 0));

	//Consider unloading gui container textures
	
	mesh.setQuadTextureCoord(glm::vec2(0, 0), glm::vec2(1, 1));

}

void GameTextureLoader::loadEntities() {

	ents[ENT_HUMAN].Load(TEXTURE_PATH + "entity/steve.png");
	ents[ENT_HUMAN_COOT].Load(TEXTURE_PATH + "entity/coot.png");

}

Texture GameTextureLoader::crop(BasicShader& shader, Transform& trans, Texture& base, glm::vec2 dim, Mesh& quad,
	glm::vec2 bottomLeft, glm::vec2 topRight) {

	GLuint buf = shader.createBuffer();//Each texture needs separate buffer for some reason
	Texture tex;
	float width = abs(topRight.x - bottomLeft.x);
	float height = abs(topRight.y - bottomLeft.y);
	tex.setIndex(shader.createTex());
	shader.updateDimensions(width, height);
	trans.SetScale(glm::vec3(width / dim.x, height / dim.y, 1));
	shader.setTransMat(trans.GetMatrix());
	base.bind();

	//Convert pixels to ratio
	glm::vec2 baseDim(base.getWidth(), base.getHeight());
	bottomLeft /= baseDim;
	topRight /= baseDim;

	quad.setQuadTextureCoord(bottomLeft, topRight);
	quad.draw();

	tex.setWidth(width);
	tex.setHeight(height);

	glDeleteFramebuffers(1, &buf);

	return tex;

}