#include "Physics.h"
#include <iostream>
#define GRAVITY 0.0002
#define dampening 0.3
#define PI 3.14159265

Physics::Physics(List* head)
{
    this->head = head;
    this->x_bound_top = 0;
    this->x_bound_down = 600;

    this->y_bound_top = 0;
    this->y_bound_down = 600;

}

Physics::Physics(int x_top, int x_down, int y_top, int y_down)
{
    this->x_bound_top = x_top;
    this->x_bound_down = x_down;
    this->y_bound_top = y_top;
    this->y_bound_down = y_down;

}

Physics::~Physics()
{
}

void Physics::boundariesCollisions(){

    // List* tmp = head;
	// while (head != NULL) {
	// 	if (head->object != nullptr) {

            

	// 	}
	// 	head = head->prev;
	// }
	// head = tmp;

}

void Physics::resolveCollisions(List* head){

    List* tmp = head;

	while (head != NULL) {
		if (head->object != nullptr) {

            std::cout << head->object->y + head->object->radius << std::endl;

            if (head->object->y  + head->object->radius > y_bound_down) {
                head->object->y = y_bound_down  - head->object->radius;
                head->object->vy *= -1 * dampening;
            }
            else if (head->object->y  - head->object->radius < y_bound_top) {
                head->object->y = y_bound_top + head->object->radius;
                head->object->vy *= -1 * dampening;
            }

            if (head->object->x  + head->object->radius > x_bound_down) {
                head->object->x = x_bound_down  - head->object->radius;
                head->object->vx *= -1 * dampening;
            }

		}
		head = head->prev;
	}
	head = tmp;
}

void Physics::gravity(List* head,double t){
    
    List* tmp = head;
	while (head != NULL) {
		if (head->object != nullptr) {

            head->object->vy -= GRAVITY*t;
            head->object->y += head->object->vy*t;

		}
		head = head->prev;
	}
	head = tmp;

}