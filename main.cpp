#include <iostream>
#include "Engine.h"
#include "GameObject.h"

Engine* eng = nullptr;

int main() {

	eng = new Engine("Fluid Simulation", 600,600);
	eng->init(false);

	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;

		if (delta > 1000 / 60.0)
		{
			std::cout << "fps: " << 1000/delta << std::endl;

			eng->handleEvents();
			eng->update(delta);
			eng->render();
			
			b = a;
		}

	}
	eng->clear();
	return 0;
}