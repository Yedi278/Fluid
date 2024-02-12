#include "GameObject.h"
#define gravity 0.0002
#define dampening 0.3

GameObject::GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id) {

	this->x = vect->xf;
	this->y = vect->yf;
	this->id = id;

}

GameObject::~GameObject() {
	delete this;
}

void GameObject::update(Uint32 t) {

	vy +=  gravity*t;
	this->y += vy * t;
	resolveCollisions();
}

void GameObject::resolveCollisions() {

	if (this->y > 580) {
		this->y = 580;
		this->vy *= -1 * dampening;
	}
}

void GameObject::render(SDL_Renderer* parent_renderer) {

	SDL_Rect* rect = new SDL_Rect();
	rect->x = this->x;
	rect->y = this->y;
	rect->w = radius;
	rect->h = radius;
	SDL_SetRenderDrawColor(parent_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(parent_renderer, rect);

}