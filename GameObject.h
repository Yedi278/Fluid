#pragma once
#include <SDL2/SDL.h>
#include "Vector2.h"

#define BASIC_TYPE 001
#define SQUARE_TYPE 002
#define CIRCLE_TYPE 003

class GameObject
{
private:

public:

	Uint8 type = BASIC_TYPE;

	float x = 0;
	float y = 0;
	float vx = 0;
	float vy = 0;
	float ax = 0;
	float ay = 0;

	float radius = 20;

	GameObject(Vector2* vect);
	GameObject(float x,float y,float vx,float vy);
	GameObject(float x,float y,float vx,float vy,float ax,float ay);
	GameObject(Vector2* vect, float radius);

	~GameObject();

	void update(Uint32 t);
	void render(SDL_Renderer* parent_renderer, SDL_Rect* rect);
	void pos(float x, float y);
};
