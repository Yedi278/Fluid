#include "GameObject.h"

GameObject::GameObject(Vector pos) {

	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

GameObject::GameObject(float x,float y,float vx,float vy) {

	this->pos.x = x;
	this->pos.y = y;
	this->vel.x = vx;
	this->vel.y = vy;

	this->color.r = rand()%255;
	this->color.g = rand()%255;
	this->color.b = rand()%255;
}

GameObject::GameObject(float x,float y,float vx,float vy,float ax,float ay) {

	this->pos.x = x;
	this->pos.y = y;
	this->vel.x = vx;
	this->vel.y = vy;
	this->acc.x = ax;
	this->acc.y = ay;
}

GameObject::GameObject(Vector pos, float radius) {

	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->radius = radius;
}

GameObject::~GameObject() {
	delete this;
}