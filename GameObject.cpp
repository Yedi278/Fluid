#ifndef IMAGESANDITEMS
#define IMAGESANDITEMS
#endif
#include "GameObject.h"

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

void GameObject::pos(float x, float y){
	this->x = x;
	this->y = y;
}

//Rubbata da internet :)
void GameObject::fill_circle(SDL_Renderer *rdr)
{
	for (double dy = 1; dy <= this->radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * this->radius * dy) - (dy * dy)));
		int x = this->x - dx;
		SDL_SetRenderDrawColor(rdr, 255,0,0,255);
		SDL_RenderDrawLine(rdr, this->x - dx, this->y + dy - this->radius, this->x + dx, this->y + dy - this->radius);
		SDL_RenderDrawLine(rdr, this->x - dx, this->y - dy + this->radius, this->x + dx, this->y - dy + this->radius);
	}
}