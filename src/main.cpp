#include "imgui"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "Engine.h"

#define FPS_LIMIT 60
#define TIME_RATE 1.3

Engine* eng = nullptr;

const float dt = 0.001;

int main(int argc, char* argv[]) {
	
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