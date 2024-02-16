#include <iostream>
#include "Engine.h"
#include "GameObject.h"

#define FPS_LIMIT 60
#define TIME_RATE 1

Engine* eng = nullptr;

int main() {
	
	eng = new Engine("Fluid Simulation", 600,600);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();
	Uint32 c = SDL_GetTicks();


	Uint16 delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;

		eng->handleEvents();
		if (delta > 1000 / FPS_LIMIT & !eng->pause)
		{	
			double time = (double)delta/1000;
			// SDL_Log("delta: %ld",delta);
			SDL_Log("FPS: %d",1000/delta);
			eng->update(TIME_RATE*time);
			b = a;
		}
		eng->render();

		c = SDL_GetTicks();
	}
	eng->clear();
	return 0;
}