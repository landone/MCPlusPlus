
#include <time.h>
#include <iostream>

#include "GameDisplay.h"
#include "Evt_Display.h"
#include "Camera.h"
#include "GameAssetLoader.h"
#include "World.h"
#include "Player.h"
#include "Graphic.h"
#include "Text.h"
#include "MDL_Human.h"
#include "ItemStack.h"

int main() {
	
	srand(clock());//Allow random number gens
	Chunk::setSeed(rand());

	GameDisplay disp(1600, 900, "MC++");
	disp.hideCursor(true);
	disp.relativeCursor(true);

	GameAssetLoader::loadAll();

	World world;
	world.getBlockAt(2, 25, 4)->setMaterial(MATERIAL::LOG_OAK);
	world.updateVisibility(world.getBlockAt(2, 25, 4));

	Player player(world);
	Camera* cam = player.getCamera();
	Camera* guiCam = Camera::create();

	double lastFrame = clock(), thisFrame = 0;

	player.setPos(2.5, 25.5, 2.5);

	double fps = 0;
	int fpsCounter = 0;
	bool printFPS = true;

	float counter = 0.0f;

	MDL_Human coot, human;
	coot.setTex(GameAssetLoader::getEntity(ENT_HUMAN_COOT));
	coot.setPos(glm::vec3(5.5, 25, 5.5));
	human.setPos(glm::vec3(6.5, 25, 5.5));

	while (disp.isOpen()) {

		counter += 0.05f;

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

		disp.gBuffer.setViewMat(guiCam->getViewMatrix());
		glDisable(GL_DEPTH_TEST);
		Evt_Display::sendDraw3DGUI(disp.gBuffer);
		disp.gBuffer.setGUI(true);
		disp.gBuffer.setViewMat(glm::mat4());
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