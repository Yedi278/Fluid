#include "Engine.h"

#define FPS_LIMIT 60
#define TIME_RATE 1

Engine* eng = nullptr;

int main() {
	
	eng = new Engine("Fluid Simulation", 700,700);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();
	Uint32 c = SDL_GetTicks();


	Uint16 delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;

		eng->handleEvents();
		if (delta > (double)1000 / FPS_LIMIT & !eng->pause){
			// SDL_Log("FPS: %d",1000/delta);
			eng->update((double)TIME_RATE*10/FPS_LIMIT);
			b = a;

		}
		
		eng->render();

	}
	eng->clear();
	return 0;
}