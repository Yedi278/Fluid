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

		std::cout << "Error Initialising SDL \n";
		std::cout << SDL_GetError() << std::endl;
	}
	else {

		std::cout << "SDL Initialised \n";

		bool flags = false;
		if (fullscreen) { flags = true; }

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		objList = new ObjectList();
		//objList->init();

		Vector2* vect = new Vector2(200,200);
		addObj(vect);
		Vector2* vect2 = new Vector2(300, 200);
		addObj(vect2);
		Vector2* vect3 = new Vector2(400, 200);
		addObj(vect3);
		
		running = true;
	}
}

void Engine::addObj(Vector2* vect) {

	GameObject* obj = new GameObject(renderer, vect ,0);
	objList->append_top(obj);
	
}

void Engine::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_q) {
			running = false;
		}
		break;
	default:
		break;
	}
}

void Engine::update(Uint32 time) {

	// Vector2* vect3 = new Vector2(400, 200);
	// addObj(vect3); 
	
	objList->update_all(time);
	counter++;
	std::cout << counter << std::endl;
}

void Engine::render() {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	objList->render_all(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Engine::clear() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}
