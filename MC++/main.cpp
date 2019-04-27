
#include <time.h>
#include <iostream>

#include "GameDisplay.h"
#include "Evt_Display.h"
#include "Camera.h"
#include "GameTextureLoader.h"
#include "World.h"
#include "Player.h"
#include "Graphic.h"

int main() {
	
	srand(clock());//Allow random number gens
	Chunk::setSeed(rand());

	GameDisplay disp(1600, 900, "MC++");
	disp.hideCursor(true);
	disp.relativeCursor(true);

	GameTextureLoader::loadMaterials();

	World world;

	Player player(world);
	Camera* cam = player.getCamera();
	Camera* guiCam = Camera::create();

	long lastFrame = clock(), thisFrame = 0;

	player.setPos(2, 6.5, 2.5);
	cam->setRot(glm::vec3());
	//cam->rotate(glm::vec3(0, -3.1415 * 135 / 180, 0));

	world.getBlockAt(2,4,2)->setMaterial(MATERIAL::BRICK);

	double fps = 0;
	int fpsCounter = 0;
	bool printFPS = false;

	float counter = 0.0f;

	Texture crosshairs;
	crosshairs.Load("./res/textures/gui/crosshairs.jpg");
	Graphic graphic(crosshairs);

	while (disp.isOpen()) {

		counter += 0.05f;

		thisFrame = clock();
		Evt_Display::sendFrame((thisFrame - lastFrame) / 1000.0);
		fps += (thisFrame - lastFrame) / 1000.0;
		lastFrame = thisFrame;

		if (printFPS) {
			fpsCounter++;
			if (fpsCounter == 10) {

				std::cout << "FPS: " << (10 / fps) << std::endl;
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