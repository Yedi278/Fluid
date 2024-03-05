#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "Physics.h"

class Engine
{
private:

	Uint16 width;
	Uint16 height;
	const char* title;
	bool running = false;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	Physics* phy = nullptr;
	Grid* grid = nullptr;
	Uint32 counter = 0;

public:

	Engine(const char* title,Uint16 width, Uint16 height);
	~Engine();

	float time_rate = 1;
	bool pause = false;

	bool circleBounds = false;
	int circleBoundRadius = 300;

	bool rectBounds = true;
	int w = 700, h = 600;

	bool collisions = true;
	float energy = 0;
	
	void init(bool fullscreen);
	void handleEvents();
	void update(double dt);
	void render();
	void moveObjects(int mx, int my);
	void renderBorders();
	void settings();

	bool isRunning() {
		return running;
	}
	void clear();

};

