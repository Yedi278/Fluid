#include "Physics.h"
#include <iostream>
#define GRAVITY 1000
#define dampening 0.3
#define PI 3.14159265

Physics::Physics(List* head)
{
    this->head = head;
    this->x_bound_top = 0;
    this->x_bound_down = 500;

    this->y_bound_top = 0;
    this->y_bound_down = 500;

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

void Physics::resolveCollisions(){


    // List* tmp = this->head;
    // std::cout << this->head->object->y << std::endl;

	// while (this->head != NULL) {
	// 	if (this->head->object != nullptr) {

    //         std::cout << this->head->object->y << std::endl;

    //         if (this->head->object->y >= this->y_bound_down) {
    //             this->head->object->y = this->y_bound_down;
    //             this->head->object->vy *= -1 * dampening;
    //         }

	// 	}
	// 	this->head = this->head->prev;
	// }
	// this->head = tmp;
}

void Physics::gravity(double t){
    
    List* tmp = head;
	while (head != NULL) {
		if (head->object != nullptr) {

            head->object->vy += GRAVITY*t;
            head->object->y += head->object->vy*t;

		}
		head = head->prev;
	}
	head = tmp;

}