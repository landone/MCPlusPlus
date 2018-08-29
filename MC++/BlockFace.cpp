#include "BlockFace.h"
#include "GameTextureLoader.h"

std::vector<Vertex> BlockFace::verts[6] = {
	{//XPositive:North
		Vertex{ glm::vec3(1,1,0),glm::vec3(1,0,0),glm::vec2(1,0) },
		Vertex{ glm::vec3(1,0,0),glm::vec3(1,0,0),glm::vec2(1,1) },
		Vertex{ glm::vec3(1,0,1),glm::vec3(1,0,0),glm::vec2(0,1) },
		Vertex{ glm::vec3(1,1,1),glm::vec3(1,0,0),glm::vec2(0,0) }
	},
	{//XNegative:South
		Vertex{ glm::vec3(0,1,1),glm::vec3(-1,0,0),glm::vec2(1,0) },
		Vertex{ glm::vec3(0,0,1),glm::vec3(-1,0,0),glm::vec2(1,1) },
		Vertex{ glm::vec3(0,0,0),glm::vec3(-1,0,0),glm::vec2(0,1) },
		Vertex{ glm::vec3(0,1,0),glm::vec3(-1,0,0),glm::vec2(0,0) }
	},
	{//ZPositive:East
		Vertex{ glm::vec3(1,1,1),glm::vec3(0,0,1),glm::vec2(1,0) },
		Vertex{ glm::vec3(1,0,1),glm::vec3(0,0,1),glm::vec2(1,1) },
		Vertex{ glm::vec3(0,0,1),glm::vec3(0,0,1),glm::vec2(0,1) },
		Vertex{ glm::vec3(0,1,1),glm::vec3(0,0,1),glm::vec2(0,0) }
	},
	{//ZNegative:West
		Vertex{ glm::vec3(0,1,0),glm::vec3(0,0,-1),glm::vec2(1,0) },
		Vertex{ glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec2(1,1) },
		Vertex{ glm::vec3(1,0,0),glm::vec3(0,0,-1),glm::vec2(0,1) },
		Vertex{ glm::vec3(1,1,0),glm::vec3(0,0,-1),glm::vec2(0,0) }
	},
	{//Up
		Vertex{ glm::vec3(0,1,1),glm::vec3(0,1,0),glm::vec2(1,0) },
		Vertex{ glm::vec3(0,1,0),glm::vec3(0,1,0),glm::vec2(1,1) },
		Vertex{ glm::vec3(1,1,0),glm::vec3(0,1,0),glm::vec2(0,1) },
		Vertex{ glm::vec3(1,1,1),glm::vec3(0,1,0),glm::vec2(0,0) }
	},
	{//Down
		Vertex{ glm::vec3(1,0,1),glm::vec3(0,-1,0),glm::vec2(1,0) },
		Vertex{ glm::vec3(1,0,0),glm::vec3(0,-1,0),glm::vec2(1,1) },
		Vertex{ glm::vec3(0,0,0),glm::vec3(0,-1,0),glm::vec2(0,1) },
		Vertex{ glm::vec3(0,0,1),glm::vec3(0,-1,0),glm::vec2(0,0) }
	}
};
std::vector<GLuint> BlockFace::indices = {//All verts defined in a counterclockwise fashion, while indices draw in a clockwise path
	2, 1, 0,
	2, 0, 3
};

bool BlockFace::meshInit = false;
Mesh** BlockFace::meshes = new Mesh*[6];

BlockFace::BlockFace(BlockFaceDirection dir, MATERIAL mat) {

	if (!meshInit) {
		meshInit = true;
		for (int i = 0; i < 6; i++) {
			meshes[i] = new Mesh(verts[i], indices);//Allocated for entirety of application run
		}
	}

	myTex = &GameTextureLoader::getMaterial(mat);
	myMesh = meshes[(int)dir];

}

void BlockFace::setMaterial(MATERIAL t) {

	myTex = &GameTextureLoader::getMaterial(t);

}

void BlockFace::draw() {

	if (!visible) {
		return;
	}

	myTex->bind();
	myMesh->draw();

}