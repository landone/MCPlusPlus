#include "GameAssetLoader.h"

Texture GameAssetLoader::mats[MATERIAL::MAX_MAT];//Allocated for entirety of application run
Texture GameAssetLoader::fonts[FONT::MAX_FONT];
Texture GameAssetLoader::gui[GUI_Component::MAX_GUI];
Texture GameAssetLoader::ents[ENTITIES::MAX_ENT];

Texture GameAssetLoader::items[ITEM::MAX_ITEM];
Mesh GameAssetLoader::items_mesh[ITEM::MAX_ITEM];

static const std::string TEXTURE_PATH = "./res/texture/";

using namespace glm;

void GameAssetLoader::loadAll() {

	loadMaterials();
	loadFonts();
	loadGUI();
	loadEntities();
	loadItems();

}

void GameAssetLoader::loadMaterials() {
	//Start at 1 to avoid AIR
	for (int i = 1; i < MATERIAL::MAX_MAT; i++) {
		mats[i].Load(TEXTURE_PATH + "material/" + Material::getName((MATERIAL)i, true) + ".png");
	}

}

void GameAssetLoader::loadFonts() {

	fonts[ASCII].Load(TEXTURE_PATH + "font/ascii.png");

}

void GameAssetLoader::loadGUI() {

	BasicShader& shader = *BasicShader::getGlobal();
	shader.setTint(vec3(1, 1, 1));
	Transform trans;
	trans.SetPos(vec3(-1, -1, 0));//Bottom left corner
	shader.setTransMat(trans.GetMatrix());
	Mesh& mesh = *Graphic::getQuadMesh();
	GLint dimensions[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dimensions);
	vec2 dimf(dimensions[2], dimensions[3]);

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
	
	mesh.setQuadTextureCoord(glm::vec2(0, 0), vec2(1, 1));

}

void GameAssetLoader::loadEntities() {

	ents[ENT_HUMAN].Load(TEXTURE_PATH + "entity/steve.png");
	ents[ENT_HUMAN_COOT].Load(TEXTURE_PATH + "entity/coot.png");

}

void GameAssetLoader::loadItems() {

	//Start at 1 to avoid empty index
	for (int i = 1; i < ITEM::MAX_ITEM; i++) {

		items[i].Load(TEXTURE_PATH + "items/" + Items::getName((ITEM)i, true) + ".png");

		int size = items[i].getWidth() * items[i].getHeight() * 4;
		GLubyte* buf = new GLubyte[size];
		glGetTextureImage(items[i].getIndex(), 0, GL_RGBA, GL_UNSIGNED_BYTE, size, buf);

		std::vector<Vertex> verts = { //Front & back faces
			Vertex{vec3(-1/4.0f, 1/2.0f, -1/64.0f), vec3(0,0,-1), vec2(1,0)},
			Vertex{vec3(-1/4.0f, 0, -1/ 64.0f), vec3(0,0,-1), vec2(1,1)},
			Vertex{vec3(1/4.0f, 0, -1/ 64.0f), vec3(0,0,-1), vec2(0,1)},
			Vertex{vec3(1/4.0f, 1/2.0f, -1/ 64.0f), vec3(0,0,-1), vec2(0,0)},

			Vertex{vec3(1/4.0f, 1/2.0f, 1/ 64.0f), vec3(0,0,-1), vec2(0,0)},
			Vertex{vec3(1/4.0f, 0, 1/ 64.0f), vec3(0,0,-1), vec2(0,1)},
			Vertex{vec3(-1/4.0f, 0, 1/ 64.0f), vec3(0,0,-1), vec2(1,1)},
			Vertex{vec3(-1/4.0f, 1/2.0f, 1/ 64.0f), vec3(0,0,-1), vec2(1,0)}
		};
		std::vector<GLuint> indices = {
			2, 1, 0, 2, 0, 3,
			6, 5, 4, 6, 4, 7
		};
		
		vec2 pxSz(0.5f / items[i].getWidth(), 0.5f / items[i].getHeight());
		int pxCount = 0;
		for (int x = 0; x < items[i].getWidth(); x++) {
			for (int y = 0; y < items[i].getHeight(); y++) {
				int index = (y * items[i].getWidth() * 4) + x * 4 + 3;//Alpha index of pixel
				if (buf[index] < 255) {
					continue;
				}
				vec2 texTR((float)x / items[i].getWidth(), (float)y / items[i].getHeight());
				vec2 texBL((float)(x + 1) / items[i].getWidth(), (float)(y + 1) / items[i].getHeight());
				if (y == 0 || buf[index - items[i].getWidth() * 4] < 255) {//Above
					vec3 pos(1/4.0f - (x+1) * pxSz.x, 1/2.0f - y * pxSz.y, -1/ 64.0f);
					verts.push_back(Vertex{ pos + vec3(0,0,1/32.0f), vec3(0,1,0), vec2(texBL.x, texTR.y) });
					verts.push_back(Vertex{ pos, vec3(0,1,0), texBL });
					verts.push_back(Vertex{ pos + vec3(pxSz.x,0,0), vec3(0,1,0), vec2(texTR.x, texBL.y) });
					verts.push_back(Vertex{ pos + vec3(pxSz.x,0,1/ 32.0f), vec3(0,1,0), texTR });
					GLuint last = indices[indices.size() - 1];
					indices.push_back(last + 3);
					indices.push_back(last + 2);
					indices.push_back(last + 1);
					indices.push_back(last + 3);
					indices.push_back(last + 1);
					indices.push_back(last + 4);
				}
				if (y == items[i].getHeight() - 1 || buf[index + items[i].getWidth() * 4] < 255) {//Below
					vec3 pos(1 / 4.0f - (x + 1) * pxSz.x, 1 / 2.0f - (y+1) * pxSz.y, -1 / 64.0f);
					verts.push_back(Vertex{ pos, vec3(0,-1,0), vec2(texBL.x, texTR.y) });
					verts.push_back(Vertex{ pos + vec3(0,0,1 / 32.0f), vec3(0,-1,0), texBL });
					verts.push_back(Vertex{ pos + vec3(pxSz.x,0,1 / 32.0f), vec3(0,-1,0), vec2(texTR.x, texBL.y) });
					verts.push_back(Vertex{ pos + vec3(pxSz.x,0,0), vec3(0,-1,0), texTR });
					GLuint last = indices[indices.size() - 1];
					indices.push_back(last + 3);
					indices.push_back(last + 2);
					indices.push_back(last + 1);
					indices.push_back(last + 3);
					indices.push_back(last + 1);
					indices.push_back(last + 4);
				}
				if (x == 0 || buf[index - 4] < 255) {//Left
					vec3 pos(1 / 4.0f - x * pxSz.x, 1 / 2.0f - y * pxSz.y, -1 / 64.0f);
					verts.push_back(Vertex{ pos, vec3(-1,0,0), vec2(texBL.x, texTR.y) });
					verts.push_back(Vertex{ pos + vec3(0,-pxSz.y,0), vec3(-1,0,0), texBL });
					verts.push_back(Vertex{ pos + vec3(0,-pxSz.y,1 / 32.0f), vec3(-1,0,0), vec2(texTR.x, texBL.y) });
					verts.push_back(Vertex{ pos + vec3(0,0,1/ 32.0f), vec3(-1,0,0), texTR });
					GLuint last = indices[indices.size() - 1];
					indices.push_back(last + 3);
					indices.push_back(last + 2);
					indices.push_back(last + 1);
					indices.push_back(last + 3);
					indices.push_back(last + 1);
					indices.push_back(last + 4);
				}
				if (x == items[i].getWidth() - 1 || buf[index + 4] < 255) {//Right
					vec3 pos(1 / 4.0f - (x+1) * pxSz.x, 1 / 2.0f - y * pxSz.y, 1 / 64.0f);
					verts.push_back(Vertex{ pos, vec3(-1,0,0), vec2(texBL.x, texTR.y) });
					verts.push_back(Vertex{ pos + vec3(0,-pxSz.y,0), vec3(-1,0,0), texBL });
					verts.push_back(Vertex{ pos + vec3(0,-pxSz.y,-1 / 32.0f), vec3(-1,0,0), vec2(texTR.x, texBL.y) });
					verts.push_back(Vertex{ pos + vec3(0,0,-1 / 32.0f), vec3(-1,0,0), texTR });
					GLuint last = indices[indices.size() - 1];
					indices.push_back(last + 3);
					indices.push_back(last + 2);
					indices.push_back(last + 1);
					indices.push_back(last + 3);
					indices.push_back(last + 1);
					indices.push_back(last + 4);
				}
			}
		}

		items_mesh[i].Init(verts, indices);
		
		delete[] buf;

	}

}

Texture GameAssetLoader::crop(BasicShader& shader, Transform& trans, Texture& base, glm::vec2 dim, Mesh& quad,
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