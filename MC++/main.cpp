
#include <time.h>
#include <iostream>

#include "GameDisplay.h"
#include "Evt_Display.h"
#include "Camera.h"
#include "GameTextureLoader.h"
#include "Chunk.h"
#include "Player.h"

int main() {
	
	srand(clock());//Allow random number gens

	GameDisplay disp(1920, 1080, "MC++");
	disp.hideCursor(true);
	disp.relativeCursor(true);

	GameTextureLoader::loadMaterials();

	Player player;
	Camera* cam = player.getCamera();

	long lastFrame = clock(), thisFrame = 0;

	player.setPos(2.5, 7, 2.5);
	cam->rotate(glm::vec3(0, -3.1415 * 135 / 180, 0));

	Chunk c1, c2(0, 1), c3(1, 0), c4(1, 1), c5(-1, 0), c6(0, -1), c7(-1, -1), c8(-1, 1), c9(1, -1);

	double fps = 0;
	int fpsCounter = 0;
	bool printFPS = true;

	while (disp.isOpen()) {

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