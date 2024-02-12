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

	int id = 0;
	Uint8 type = BASIC_TYPE;

	float x = 0;
	float y = 0;
	float vx = 0;
	float vy = 0;
	float radius = 20;


	GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id);
	GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id, float radius);

	~GameObject();

	void update(Uint32 t);
	void render(SDL_Renderer* parent_renderer);
	void collider();
};
