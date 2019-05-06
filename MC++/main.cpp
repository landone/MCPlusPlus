
#include <time.h>
#include <iostream>

#include "GameDisplay.h"
#include "Evt_Display.h"
#include "Camera.h"
#include "GameTextureLoader.h"
#include "World.h"
#include "Player.h"
#include "Graphic.h"
#include "Text.h"
#include "MDL_Human.h"

int main() {
	
	srand(clock());//Allow random number gens
	Chunk::setSeed(rand());

	GameDisplay disp(1600, 900, "MC++");
	disp.hideCursor(true);
	disp.relativeCursor(true);

	GameTextureLoader::loadMaterials();
	GameTextureLoader::loadFonts();
	GameTextureLoader::loadGUI();
	GameTextureLoader::loadEntities();

	World world;

	Player player(world);
	Camera* cam = player.getCamera();
	Camera* guiCam = Camera::create();

	long lastFrame = clock(), thisFrame = 0;

	player.setPos(2, 26.5, 2.5);
	cam->setRot(glm::vec3());

	world.getBlockAt(2,4,2)->setMaterial(MATERIAL::BRICK);

	double fps = 0;
	int fpsCounter = 0;
	bool printFPS = true;

	float counter = 0.0f;

	Graphic crosshair(GameTextureLoader::getGUI(GUI_CROSSHAIR));
	Graphic hotbar(GameTextureLoader::getGUI(GUI_HOTBAR));
	hotbar.trans.SetPos(glm::vec3(hotbar.trans.GetPos().x, -1, 0));
	Text text("Bottom Text");
	Text thanos("THANOS TEXT");
	thanos.setSize(0.12);
	thanos.setColor(glm::vec3(0.6, 0.4, 1));
	thanos.getGraphic().trans.SetPos(glm::vec3(-1, -1 + 0.12, 0));
	text.setSize(0.12);
	text.setColor(glm::vec3(1, 1, 0));

	MDL_Human coot, human;
	coot.setTex(GameTextureLoader::getEntity(ENT_HUMAN_COOT));
	coot.setPos(glm::vec3(5.5, 25, 5.5));
	human.setTex(GameTextureLoader::getEntity(ENT_HUMAN));
	human.setPos(glm::vec3(6.5, 25, 5.5));

	while (disp.isOpen()) {

		counter += 0.05f;

		coot.setArmRotation(glm::vec3(sin(counter*2)*3.1415/3, 0, 0), false);
		coot.setArmRotation(glm::vec3(cos(counter*2) * 3.1415 / 3, 0, 0), true);

		thisFrame = clock();
		Evt_Display::sendFrame((thisFrame - lastFrame) / 1000.0);
		fps += (thisFrame - lastFrame) / 1000.0;
		lastFrame = thisFrame;

		if (printFPS) {
			fpsCounter++;
			if (fpsCounter == 10) {

				//std::cout << "FPS: " << (10 / fps) << std::endl;
				fpsCounter = 0;
				fps = 0.0;

			}
		}

		disp.gBuffer.bind();
		disp.gBuffer.setViewMat(cam->getViewMatrix());
		Evt_Display::sendDrawGeometry(disp.gBuffer);

		//disp.gBuffer.setViewMat(guiCam->getViewMatrix());
		disp.gBuffer.setGUI(true);
		glDisable(GL_DEPTH_TEST);
		Evt_Display::sendDrawGUI(disp.gBuffer);
		glEnable(GL_DEPTH_TEST);
		disp.gBuffer.setGUI(false);

		disp.lightShader.bind();
		disp.lightShader.setCameraPos(cam->getPos());
		disp.lightShader.drawQuad();

		disp.postProcessor.bind();
		disp.postProcessor.drawQuad();

		disp.update();

	}

	Texture::unloadAll();
	Entity::clearEntities();

	return 0;

}