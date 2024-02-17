#pragma once
#include <SDL2/SDL.h>
#undef main
#include "GameObject.h"
#include "ObjectArray.h"
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

	ObjectList* objList = nullptr;
	ObjectArray* objArr = nullptr;
	Physics* phy = nullptr;
	Uint32 counter = 0;

public:

	Engine(const char* title,Uint16 width, Uint16 height);
	~Engine();

	bool pause = false;
	void init(bool fullscreen);
	void addObj(int index, int x, int y);
	void handleEvents();
	void update(double time);
	void render();
	void moveObjects(int mx, int my);

	bool isRunning() {
		return running;
	}
	void clear();

};

