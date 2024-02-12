#include "GameObject.h"
#define dampening 0.3

GameObject::GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id) {

	this->x = vect->xf;
	this->y = vect->yf;
	this->id = id;

}

GameObject::GameObject(SDL_Renderer* prtRndr, Vector2* vect, int id, float radius) {

	this->x = vect->xf;
	this->y = vect->yf;
	this->id = id;
	this->radius = radius;

}

GameObject::~GameObject() {
	delete this;
}

void GameObject::update(Uint32 t) {

	// vy +=  gravity*t;
	// this->y += vy * t;
	// collider();

}

// void GameObject::collider() {

// 	if (this->y > 580) {
// 		this->y = 580;
// 		this->vy *= -1 * dampening;
// 	}
// }

void GameObject::render(SDL_Renderer* parent_renderer) {

	SDL_Rect* rect = new SDL_Rect();
	rect->x = this->x + this->radius;
	rect->y = this->y + this->radius;
	rect->w = radius*2;
	rect->h = radius*2;
	SDL_SetRenderDrawColor(parent_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(parent_renderer, rect);

}