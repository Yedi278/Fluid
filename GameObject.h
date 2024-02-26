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

	Vector pos = Vector(0,0);
	Vector vel = Vector(0,0);
	Vector acc = Vector(0,0);
	

	float m = 0;  //mass
	float radius = 30;

	GameObject(Vector vect);
	GameObject(Vector vect, float radius);
	GameObject(float x,float y,float vx,float vy);
	GameObject(float x,float y,float vx,float vy,float ax,float ay);

	~GameObject();
	
	void fill_circle(SDL_Renderer *rdr);
};