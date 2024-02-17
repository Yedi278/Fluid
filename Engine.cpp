#include "Engine.h"
#include "Grid.h"

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
		
		objArr = new ObjectArray(renderer, 2000);
		phy = new Physics(objArr,window);


		running = true;
	}
}

void Engine::addObj(int index, int x, int y) {

	objArr->add(index,x,y);
	
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
		if(event.button.button == SDL_BUTTON_LEFT){
			int posx;
			int posy;
			SDL_GetMouseState(&posx,&posy);
			moveObjects(posx,posy);
		}
		break;
	}
}

void Engine::update(double time) {


	phy->update(time);
	phy->gravity(time);
	phy->boundariesCollisions();
	phy->resolveCollisions(time);
	phy->boundariesCollisions();
	phy->resolveCollisions(time);

	if(counter <= objArr->size && counter < 100){
		addObj(counter,200,200);
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
	SDL_Quit();

}

void Engine::moveObjects(int mx,int my){

	for(int i=0; i<objArr->size; i++){
		GameObject* tmp = objArr->array[i].obj;
		if(tmp != nullptr){
			if(tmp->x - tmp->radius < mx  && mx < tmp->x + tmp->radius 
				& tmp->y - tmp->radius < my && my < tmp->y + tmp->radius){
					
					tmp->x = mx;
					tmp->y = my;
			}
		}

	}

}