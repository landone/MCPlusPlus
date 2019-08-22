#include "MDL_Human.h"
#include "GameAssetLoader.h"

using namespace glm;

static const float pxSz = 1 / 16.0f;
static const float txSz = 1 / 64.0f;
bool MDL_Human::initialized = false;
Mesh MDL_Human::meshes[6];

std::vector<Vertex> MDL_Human::verts[6] = {
{//Head
	Vertex{vec3(-4, 8, -4) * pxSz, vec3(0,0,-1), vec2(16,8) * txSz},
	Vertex{vec3(-4, 0, -4) * pxSz, vec3(0,0,-1), vec2(16,16) * txSz},
	Vertex{vec3(4, 0, -4) * pxSz, vec3(0,0,-1), vec2(8,16) * txSz},
	Vertex{vec3(4, 8, -4) * pxSz, vec3(0,0,-1), vec2(8,8) * txSz},

	Vertex{vec3(-4, 8, 4) * pxSz, vec3(-1,0,0), vec2(24,8) * txSz},
	Vertex{vec3(-4, 0, 4) * pxSz, vec3(-1,0,0), vec2(24,16) * txSz},
	Vertex{vec3(-4, 0, -4) * pxSz, vec3(-1,0,0), vec2(16,16) * txSz},
	Vertex{vec3(-4, 8, -4) * pxSz, vec3(-1,0,0), vec2(16,8) * txSz},

	Vertex{vec3(4, 8, 4) * pxSz, vec3(0,0,1), vec2(32,8) * txSz},
	Vertex{vec3(4, 0, 4) * pxSz, vec3(0,0,1), vec2(32,16) * txSz},
	Vertex{vec3(-4, 0, 4) * pxSz, vec3(0,0,1), vec2(24,16) * txSz},
	Vertex{vec3(-4, 8, 4) * pxSz, vec3(0,0,1), vec2(24,8) * txSz},

	Vertex{vec3(4, 8, -4) * pxSz, vec3(1,0,0), vec2(8,8) * txSz},
	Vertex{vec3(4, 0, -4) * pxSz, vec3(1,0,0), vec2(8,16) * txSz},
	Vertex{vec3(4, 0, 4) * pxSz, vec3(1,0,0), vec2(0,16) * txSz},
	Vertex{vec3(4, 8, 4) * pxSz, vec3(1,0,0), vec2(0,8) * txSz},

	Vertex{vec3(-4, 8, 4) * pxSz, vec3(0,1,0), vec2(16,0) * txSz},
	Vertex{vec3(-4, 8, -4) * pxSz, vec3(0,1,0), vec2(16,8) * txSz},
	Vertex{vec3(4, 8, -4) * pxSz, vec3(0,1,0), vec2(8,8) * txSz},
	Vertex{vec3(4, 8, 4) * pxSz, vec3(0,1,0), vec2(8,0) * txSz},

	Vertex{vec3(-4, 0, -4) * pxSz, vec3(0,-1,0), vec2(24,0) * txSz},
	Vertex{vec3(-4, 0, 4) * pxSz, vec3(0,-1,0), vec2(24,8) * txSz},
	Vertex{vec3(4, 0, 4) * pxSz, vec3(0,-1,0), vec2(16,8) * txSz},
	Vertex{vec3(4, 0, -4) * pxSz, vec3(0,-1,0), vec2(16,0) * txSz}
},
{//Body
	Vertex{vec3(-4, 12, -2) * pxSz, vec3(0,0,-1), vec2(28,20) * txSz},
	Vertex{vec3(-4, 0, -2) * pxSz, vec3(0,0,-1), vec2(28,32) * txSz},
	Vertex{vec3(4, 0, -2) * pxSz, vec3(0,0,-1), vec2(20,32) * txSz},
	Vertex{vec3(4, 12, -2) * pxSz, vec3(0,0,-1), vec2(20,20) * txSz},

	Vertex{vec3(-4, 12, 2) * pxSz, vec3(-1,0,0), vec2(32,20) * txSz},
	Vertex{vec3(-4, 0, 2) * pxSz, vec3(-1,0,0), vec2(32,32) * txSz},
	Vertex{vec3(-4, 0, -2) * pxSz, vec3(-1,0,0), vec2(28,32) * txSz},
	Vertex{vec3(-4, 12, -2) * pxSz, vec3(-1,0,0), vec2(28,20) * txSz},

	Vertex{vec3(4, 12, 2) * pxSz, vec3(0,0,1), vec2(40,20) * txSz},
	Vertex{vec3(4, 0, 2) * pxSz, vec3(0,0,1), vec2(40,32) * txSz},
	Vertex{vec3(-4, 0, 2) * pxSz, vec3(0,0,1), vec2(32,32) * txSz},
	Vertex{vec3(-4, 12, 2) * pxSz, vec3(0,0,1), vec2(32,20) * txSz},

	Vertex{vec3(4, 12, -2) * pxSz, vec3(1,0,0), vec2(20,20) * txSz},
	Vertex{vec3(4, 0, -2) * pxSz, vec3(1,0,0), vec2(20,32) * txSz},
	Vertex{vec3(4, 0, 2) * pxSz, vec3(1,0,0), vec2(16,32) * txSz},
	Vertex{vec3(4, 12, 2) * pxSz, vec3(1,0,0), vec2(16,20) * txSz},

	Vertex{vec3(-4, 12, 2) * pxSz, vec3(0,1,0), vec2(28,16) * txSz},
	Vertex{vec3(-4, 12, -2) * pxSz, vec3(0,1,0), vec2(28,20) * txSz},
	Vertex{vec3(4, 12, -2) * pxSz, vec3(0,1,0), vec2(20,20) * txSz},
	Vertex{vec3(4, 12, 2) * pxSz, vec3(0,1,0), vec2(20,16) * txSz},

	Vertex{vec3(-4, 0, -2) * pxSz, vec3(0,-1,0), vec2(36,16) * txSz},
	Vertex{vec3(-4, 0, 2) * pxSz, vec3(0,-1,0), vec2(36,20) * txSz},
	Vertex{vec3(4, 0, 2) * pxSz, vec3(0,-1,0), vec2(28,20) * txSz},
	Vertex{vec3(4, 0, -2) * pxSz, vec3(0,-1,0), vec2(28,16) * txSz}
},
{//LeftLeg
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,0,-1), vec2(8,20) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,0,-1), vec2(8,32) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,0,-1), vec2(4,32) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,0,-1), vec2(4,20) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(-1,0,0), vec2(12,20) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(-1,0,0), vec2(12,32) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(-1,0,0), vec2(8,32) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(-1,0,0), vec2(8,20) * txSz},

	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,0,1), vec2(16,20) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,0,1), vec2(16,32) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,0,1), vec2(12,32) * txSz},
	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,0,1), vec2(12,20) * txSz},

	Vertex{vec3(2, 0, -2) * pxSz, vec3(1,0,0), vec2(4,20) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(1,0,0), vec2(4,32) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(1,0,0), vec2(0,32) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(1,0,0), vec2(0,20) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,1,0), vec2(8,16) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,1,0), vec2(8,20) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,1,0), vec2(4,20) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,1,0), vec2(4,16) * txSz},

	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,-1,0), vec2(12,16) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,-1,0), vec2(12,20) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,-1,0), vec2(8,20) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,-1,0), vec2(8,16) * txSz}
},
{//RightLeg
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,0,-1), vec2(24,52) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,0,-1), vec2(24,64) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,0,-1), vec2(20,64) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,0,-1), vec2(20,52) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(-1,0,0), vec2(28,52) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(-1,0,0), vec2(28,64) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(-1,0,0), vec2(24,64) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(-1,0,0), vec2(24,53) * txSz},

	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,0,1), vec2(32,52) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,0,1), vec2(32,64) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,0,1), vec2(28,64) * txSz},
	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,0,1), vec2(28,52) * txSz},

	Vertex{vec3(2, 0, -2) * pxSz, vec3(1,0,0), vec2(20,52) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(1,0,0), vec2(20,64) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(1,0,0), vec2(16,64) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(1,0,0), vec2(16,52) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,1,0), vec2(24,48) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,1,0), vec2(24,52) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,1,0), vec2(20,52) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,1,0), vec2(20,48) * txSz},

	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,-1,0), vec2(28,48) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,-1,0), vec2(28,52) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,-1,0), vec2(24,52) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,-1,0), vec2(24,48) * txSz}
},
{//LeftArm
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,0,-1), vec2(48,20) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,0,-1), vec2(48,32) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,0,-1), vec2(44,32) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,0,-1), vec2(44,20) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(-1,0,0), vec2(52,20) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(-1,0,0), vec2(52,32) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(-1,0,0), vec2(48,32) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(-1,0,0), vec2(48,20) * txSz},

	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,0,1), vec2(56,20) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,0,1), vec2(56,32) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,0,1), vec2(52,32) * txSz},
	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,0,1), vec2(52,20) * txSz},

	Vertex{vec3(2, 0, -2) * pxSz, vec3(1,0,0), vec2(44,20) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(1,0,0), vec2(44,32) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(1,0,0), vec2(40,32) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(1,0,0), vec2(40,20) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,1,0), vec2(48,16) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,1,0), vec2(48,20) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,1,0), vec2(44,20) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,1,0), vec2(44,16) * txSz},

	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,-1,0), vec2(52,16) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,-1,0), vec2(52,20) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,-1,0), vec2(48,20) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,-1,0), vec2(48,16) * txSz}
},
{//RightArm
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,0,-1), vec2(40,52) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,0,-1), vec2(40,64) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,0,-1), vec2(36,64) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,0,-1), vec2(36,52) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(-1,0,0), vec2(44,52) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(-1,0,0), vec2(44,64) * txSz},
	Vertex{vec3(-2, -12, -2) * pxSz, vec3(-1,0,0), vec2(40,64) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(-1,0,0), vec2(40,52) * txSz},

	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,0,1), vec2(48,52) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,0,1), vec2(48,64) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,0,1), vec2(44,64) * txSz},
	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,0,1), vec2(44,52) * txSz},

	Vertex{vec3(2, 0, -2) * pxSz, vec3(1,0,0), vec2(36,52) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(1,0,0), vec2(36,64) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(1,0,0), vec2(32,64) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(1,0,0), vec2(32,52) * txSz},

	Vertex{vec3(-2, 0, 2) * pxSz, vec3(0,1,0), vec2(40,48) * txSz},
	Vertex{vec3(-2, 0, -2) * pxSz, vec3(0,1,0), vec2(40,52) * txSz},
	Vertex{vec3(2, 0, -2) * pxSz, vec3(0,1,0), vec2(36,52) * txSz},
	Vertex{vec3(2, 0, 2) * pxSz, vec3(0,1,0), vec2(36,48) * txSz},

	Vertex{vec3(-2, -12, -2) * pxSz, vec3(0,-1,0), vec2(44,48) * txSz},
	Vertex{vec3(-2, -12, 2) * pxSz, vec3(0,-1,0), vec2(44,52) * txSz},
	Vertex{vec3(2, -12, 2) * pxSz, vec3(0,-1,0), vec2(40,52) * txSz},
	Vertex{vec3(2, -12, -2) * pxSz, vec3(0,-1,0), vec2(40,48) * txSz}
}
};

std::vector<GLuint> MDL_Human::indices = {
	2, 1, 0, 2, 0, 3,
	6, 5, 4, 6, 4, 7,
	10, 9, 8, 10, 8, 11,
	14, 13, 12, 14, 12, 15,
	18, 17, 16, 18, 16, 19,
	22, 21, 20, 22, 20, 23
};

MDL_Human::MDL_Human() {

	if (!initialized) {
		initialized = true;

		for (int i = 0; i < 6; i++) {
			meshes[i].Init(verts[i], indices);
		}

	}

	tex = GameAssetLoader::getEntity(ENT_HUMAN);
	setPos(vec3(0,0,0));

}

glm::vec3 MDL_Human::getHandPos(bool right, bool tip) {

	int index = right ? 5 : 4;
	glm::vec3 radius(0, verts[5][1].position.y, tip ? -4 * pxSz : 0);
	return trans[index].GetPos() + glm::vec3((trans[index].GetRotMatrix() * trans[index].GetScaleMatrix()) * glm::vec4(radius, 1.0f));
}

glm::vec3 MDL_Human::getArmRot(bool right) {
	return trans[right ? 5 : 4].GetRot();
}

void MDL_Human::setPos(vec3 pos) {

	trans[1].SetPos(pos + vec3(0,12,0) * pxSz);
	updatePositions();

}

void MDL_Human::setTex(Texture tex) {

	this->tex = tex;

}

void MDL_Human::setHeadRotation(vec3 rot) {

	rots[0] = rot;
	trans[0].SetRot(rot);

}

void MDL_Human::setArmRotation(vec3 rot, bool right) {

	rots[right ? 5 : 4] = rot;
	trans[right ? 5 : 4].SetRot(rot + trans[1].GetRot());

}

void MDL_Human::setLegRotation(vec3 rot, bool right) {

	rots[right ? 3 : 2] = rot;
	trans[right ? 3 : 2].SetRot(rot + trans[1].GetRot());

}

void MDL_Human::setBodyRotation(vec3 rot) {
	trans[1].SetRot(rot);
	updatePositions();
	updateRotations();
}

void MDL_Human::onDrawGeometry(GBuffer& gBuf) {

	if (!visible) {
		return;
	}
	tex.bind();
	for (int i = 0; i < 6; i++) {
		gBuf.setTransMat(trans[i].GetMatrix());
		gBuf.setRotMat(trans[i].GetRotMatrix());
		meshes[i].draw();
	}

}

void MDL_Human::updatePositions() {

	mat4 bod = trans[1].GetMatrix();
	trans[0].SetPos(vec3(bod * vec4(vec3(0, 12, 0) * pxSz, 1)));
	trans[2].SetPos(vec3(bod * vec4(vec3(-2, 0, 0) * pxSz, 1)));
	trans[3].SetPos(vec3(bod * vec4(vec3(2, 0, 0) * pxSz, 1)));
	trans[4].SetPos(vec3(bod * vec4(vec3(-6, 12, 0) * pxSz, 1)));
	trans[5].SetPos(vec3(bod * vec4(vec3(6, 12, 0) * pxSz, 1)));

}

void MDL_Human::updateRotations() {

	vec3 rot = trans[1].GetRot();
	trans[0].SetRot(rots[0] + rot);
	trans[2].SetRot(rots[2] + rot);
	trans[3].SetRot(rots[3] + rot);
	trans[4].SetRot(rots[4] + rot);
	trans[5].SetRot(rots[5] + rot);

}