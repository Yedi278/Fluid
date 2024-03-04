#include "Engine.h"

#define FPS_LIMIT 60
#define TIME_RATE 1.3

Engine* eng = nullptr;

const float dt = 0.001;

int main(int argc, char* argv[]) {
	
	eng = new Engine("Fluid Simulation", 800,700);
	eng->init(false);

	Uint32 a = SDL_GetTicks();
	Uint32 b = SDL_GetTicks();

	Uint16 delta = 0;
	double dt = 0.;
	while (eng->isRunning()) {

		a = SDL_GetTicks();
		delta = a - b;

		eng->handleEvents();
		
		if (delta > (double)1000 / FPS_LIMIT && !eng->pause){
			// SDL_Log("FPS: %d",1000/delta);
			
			while(dt < (double)TIME_RATE*10/FPS_LIMIT){
				
				eng->update(0.01);
				dt += 0.01;

			}
			b = a;
		}
		dt = 0.;
		
		eng->render();

	}
	eng->clear();
	return 0;
}