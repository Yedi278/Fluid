#include "Engine.h"
#include <iostream>

Engine::Engine(const char* title, Uint16 width, Uint16 height) {

	this->title = title;
	this->width = width;
	this->height = height;
}

Engine::~Engine() {
	delete this;
}

void Engine::init(bool fullscreen) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

		SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Error Initialising SDL \n%s",SDL_GetError());
	}
	else {

		SDL_Log("SDL Initialised Successfully\n");
		bool flags = false;
		if (fullscreen) { flags = true; }

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		
		objArr = new ObjectArray(renderer, 7);
		// objArr->init(window);
		
		phy = new Physics(objArr);
		
		running = true;
	}
}

void Engine::addObj(int index) {

	objArr->add(index);
	
}

void Engine::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_SPACE) {
			if(pause){ 
				SDL_SetWindowTitle(window,"Fluid Simulation ~ [Running]");
				pause = false;
			}
			else{
				SDL_SetWindowTitle(window,"Fluid Simulation ~ [Pause]");
				pause = true;
			}
		}
		break;
	default:
		break;
	}
}

void Engine::update(double time) {

	phy->gravity(time);
	phy->boundariesCollisions();
	phy->resolveCollisions(time);

	if(counter < 30 ){
		addObj(counter);
	}
	counter++;
}

void Engine::render() {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	objArr->render_all();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Engine::clear() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	// delete objArr;
	// delete phy;
	SDL_Quit();

}
