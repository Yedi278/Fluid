#include "Engine.hpp"
#undef main
#define FPS_LIMIT 60

Engine* eng = nullptr;

int freq = 1000;
double dt = 0;

int main(int argv, const char** args) {
	
	eng = new Engine("Fluid Simulation", 800,700);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();

	Uint16 delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;

		eng->handleEvents();
		
		// if (delta > (double)1000 / FPS_LIMIT && !eng->pause){
		// 	// SDL_Log("FPS: %d",1000/delta);
			
		// 	eng->update((double)delta/1000);
		// 	b = a;
		// }

		dt = 0;
		const float inc = (1.f/60.f) / freq;
		while(dt < 1.f/60.f){

			eng->update(dt);
			dt += inc;


		}

		eng->render();

	}
	eng->clear();
	return 0;
}