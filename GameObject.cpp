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

//Rubbata da internet :)
void GameObject::fill_circle(SDL_Renderer *rdr)
{
	for (double dy = 1; dy <= this->radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * this->radius * dy) - (dy * dy)));
		int x = this->pos.x - dx;
		SDL_SetRenderDrawColor(rdr, 255,0,0,255);
		SDL_RenderDrawLine(rdr, this->pos.x - dx, this->pos.y + dy - this->radius, this->pos.x + dx, this->pos.y + dy - this->radius);
		SDL_RenderDrawLine(rdr, this->pos.x - dx, this->pos.y - dy + this->radius, this->pos.x + dx, this->pos.y - dy + this->radius);
	}
}