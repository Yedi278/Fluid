#pragma once
#include <SDL2/SDL.h>
#include "Vector.hpp"

#define BASIC_TYPE 001
#define SQUARE_TYPE 002
#define CIRCLE_TYPE 003

struct Color{
	int r = 255;
	int g = 255;
	int b = 255;
};

class GameObject
{
private:

public:

	Uint8 type = BASIC_TYPE;

	Vector pos = Vector(0,0);
	Vector vel = Vector(0,0);
	Vector acc = Vector(0,0);
	Vector other = Vector(0,0);;

	float m = 1;  //mass
	float radius = 20;

	Color color;

	GameObject(Vector vect);
	GameObject(Vector vect, float radius);
	GameObject(float x,float y,float vx,float vy);
	GameObject(float x,float y,float vx,float vy,float ax,float ay);

	~GameObject();
};