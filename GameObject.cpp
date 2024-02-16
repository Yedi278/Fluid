#ifndef IMAGESANDITEMS
#define IMAGESANDITEMS
#endif

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

void GameObject::pos(float x, float y){

	this->x = x;
	this->y = y;
}

void GameObject::update(Uint32 t){
}

void fill_circle(SDL_Renderer *rdr, int cx, int cy, int radius)
{
	//Rubbata da internet :)
	static const int BPP = 4;

	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(rdr, 255,0,0,255);
		SDL_RenderDrawLine(rdr, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(rdr, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
		
	}
}

void GameObject::render(SDL_Renderer* parent_renderer) {

	// rect->x = this->x - this->radius;
	// rect->y = this->y - this->radius;
	// rect->w = radius*2;
	// rect->h = radius*2;
	// SDL_RenderFillRect(parent_renderer, rect);

	fill_circle(parent_renderer,this->x,this->y,this->radius);

}
