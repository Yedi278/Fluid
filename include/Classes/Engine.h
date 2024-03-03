#pragma once
#include <SDL2/SDL.h>
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

	bool pause = false;
	bool circleBounds = true;
	int circleBoundRadius = 300;

	float energy = 0;
	
	void init(bool fullscreen);
	void handleEvents();
	void update(double time);
	void render();
	void moveObjects(int mx, int my);
	void renderBorders();

	bool isRunning() {
		return running;
	}
	void clear();

};

