#include <iostream>
#include "Engine.h"
#include "GameObject.h"

#define FPS_LIMIT 30
#define TIME_RATE 0.4

Engine* eng = nullptr;

int main() {
	
	eng = new Engine("Fluid Simulation", 600,600);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();

	Uint32 delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;
		// SDL_Log("FPS: %lf",1000/delta);

		eng->handleEvents();
		if (delta > 1000 / FPS_LIMIT && !eng->pause)
		{	
			double time = delta/1000;
			eng->update(TIME_RATE*time);
			
			b = a;
		}
		eng->render();


	}
	eng->clear();
	return 0;
}