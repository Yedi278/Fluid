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
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io= ImGui::GetIO();
		(void) io;

		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer2_Init(renderer);

		grid = new Grid(window,renderer);
		phy = new Physics(window,grid);
		
		running = true;
	}
}

void Engine::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	ImGui_ImplSDL2_ProcessEvent(&event);
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

void Engine::update(double dt) {

	dt*= time_rate;
	phy->update(dt);
	if(collisions) phy->resolveCollisions(dt, renderer);
	if(circleBounds) phy->circBounds(Vector(width/2,height/2), 
					circleBoundRadius, dt);
	phy->gravity(dt);
	grid->clean();
	grid->update();
	energy = phy->Energy();

	// printf("Energy: %f\n",energy);

	while(counter < 1){
		grid->put(150,300);
		grid->put(200,300);

		counter ++;
	}
}

void Engine::settings(){

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);

	ImGui::NewFrame();
	ImGui::Begin("Settings");
	ImGui::Checkbox("Circle Bounds", &circleBounds);
	ImGui::Checkbox("Collisions", &collisions);
	ImGui::SliderFloat("Gravity",&phy->gravity_const, 0, 20);
	ImGui::SliderFloat("Time Rate",&time_rate, 0, 2);
	ImGui::SliderFloat("Dampening Factor",&phy->dampening, 0, 1);
	ImGui::End();
	ImGui::Render();

}

void Engine::render() {

	settings();	

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	grid->renderAll();
	if(circleBounds) renderBorders();

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Engine::renderBorders(){
	
	SDL_RenderDrawCircle(renderer,width/2,height/2,circleBoundRadius);

}

void Engine::clear() {

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

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