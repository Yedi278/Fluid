#pragma once
#include <SDL2/SDL.h>
#include "Vector2.h"

#define BASIC_TYPE 001
#define SQUARE_TYPE 002


class GameObject
{
private:

public:
	Uint8 type = BASIC_TYPE;
	float vx = 0;
	float vy = 0;
	int id = 0;
	int radius = 30;
	float x = 0;
	float y = 0;


	GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id);
	~GameObject();

	void update(Uint32 t);
	void render(SDL_Renderer* parent_renderer);
	void resolveCollisions();
};
