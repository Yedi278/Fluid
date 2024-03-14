#include "Engine.hpp"
#undef main
#define FPS_LIMIT 60.f

Engine* eng = nullptr;

int freq = 100;
double dt = 0;
const double inc = (double)(1.f/FPS_LIMIT) / (double)freq;


int main(int argv, const char** args) {
	
	eng = new Engine("Fluid Simulation", 800,700);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();

	Uint16 delta = 0;

	while (eng->isRunning()) {

		a = SDL_GetTicks();
		
		dt = 0.f;
		while(SDL_GetTicks()-a < 1000/FPS_LIMIT){

			
			eng->handleEvents();
			while(dt < 1.f/FPS_LIMIT){

				eng->update(dt);
				dt += inc;
				eng->handleEvents();

			}

			eng->render();
		}
		SDL_Log("FPS: %f", 1000.f/(float)(SDL_GetTicks()-a));
	}

	eng->clear();
	return 0;
}