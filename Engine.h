#pragma once
#include <SDL2/SDL.h>
#undef main
#include "GameObject.h"
#include "ObjectList.h"

class Engine
{
private:
	Uint16 width;
	Uint16 height;
	const char* title;
	bool running = false;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	ObjectList* objList = nullptr;
	Uint32 counter = 0;

public:

	Engine(const char* title,Uint16 width, Uint16 height);
	~Engine();

	void init(bool fullscreen);
	void addObj(Vector2* vect);
	void handleEvents();
	void update(Uint32 time);
	void render();
	void clear();

	bool isRunning() {
		return running;
	}

};

