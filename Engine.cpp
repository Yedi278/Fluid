#include "Engine.h"

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
		
		grid = new Grid(window,renderer);
		phy = new Physics(window,grid);
		
		running = true;
	}
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

	phy->gravity(time);
	phy->resolveCollisions(time);
	phy->update(time);
	phy->circBounds(Vector(width/2,height/2), circleBoundRadius, time);
	grid->clean();
	grid->update();

	while(counter < 2){

		grid->put(150,300);
		counter ++;
	}

}

void Engine::render() {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	grid->renderAll();
	renderBorders();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Engine::renderBorders(){
	
	SDL_RenderDrawCircle(renderer,width/2,height/2,circleBoundRadius);

}

void Engine::clear() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Log("Engine Closed!\n");
	SDL_Quit();
	
}

void Engine::moveObjects(int mx,int my){

	const Vector mouse = Vector(mx,my);
	for(auto node: grid->objects){
		if(node.obj != nullptr){

			if((node.obj->pos - mouse).mod() < node.obj->radius){
				node.obj->pos = mouse;
				node.obj->vel = Vector(0,0);
			}

		}
	}
}