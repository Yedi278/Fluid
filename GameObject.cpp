#include "GameObject.h"
#define dampening 0.3

GameObject::GameObject(Vector2* vect) {

	this->x = vect->xf;
	this->y = vect->yf;
}

GameObject::GameObject(float x,float y,float vx,float vy) {

	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

GameObject::GameObject(float x,float y,float vx,float vy,float ax,float ay) {

	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->ax = ax;
	this->ay = ay;
}

GameObject::GameObject(Vector2* vect, float radius) {

	this->x = vect->xf;
	this->y = vect->yf;
	this->radius = radius;

}

GameObject::~GameObject() {
	delete this;
}

void GameObject::render(SDL_Renderer* parent_renderer, SDL_Rect* rect) {

	rect->x = this->x - this->radius;
	rect->y = this->y - this->radius;
	rect->w = radius*2;
	rect->h = radius*2;
	SDL_RenderFillRect(parent_renderer, rect);
	// delete rect;
}

void GameObject::pos(float x, float y){

	this->x = x;
	this->y = y;
}

void GameObject::update(Uint32 t){
}