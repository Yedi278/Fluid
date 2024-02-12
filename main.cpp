#include <iostream>
#include "Engine.h"
#include "GameObject.h"
#define FPS_LIMIT 60

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

		eng->handleEvents();
		if (delta > 1000 / FPS_LIMIT)
		{
			// SDL_Log("FPS: %f",1000/delta);
			eng->update(delta);
			
			b = a;
		}
		eng->render();

	}
	eng->clear();
	return 0;
}