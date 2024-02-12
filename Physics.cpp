#include <iostream>
#include <algorithm>

#include "Physics.h"
#include "math.h"

#define GRAVITY 0.0002
#define dampening 0.2
#define dampening2 0.3


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
    if(this != nullptr){
        // std::cout << this;
        delete this;
    }
}

void Physics::boundariesCollisions(List* head){

    List* tmp = head;

	while (head != NULL) {
		if (head->object != nullptr) {

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
            else if (head->object->x  - head->object->radius < x_bound_top) {
                head->object->x = x_bound_top + head->object->radius;
                head->object->vx *= -1 * dampening;
            }

		}
		head = head->prev;
	}
	head = tmp;
}

double distance(GameObject* obj1, GameObject* obj2){

    return sqrt(pow((obj1->x-obj2->x),2) + pow((obj1->y-obj2->y),2));
}

void Physics::resolveCollisions(List* head){
    
    List* tmp = head;
        while (head != NULL) {
            if (head->object != nullptr) {
                
                ////////////////////////////
                List* tmp2 = head;
                head = tmp;
                while (head != NULL) {
                    if (head->object != nullptr) {

                        if(head != tmp2){

                            double d = distance(tmp2->object,head->object) - tmp2->object->radius - head->object->radius;
                            if(d < 1){
                                srand(time(nullptr));
                                double ang = Vector2(0,0).get_angle(tmp2->object->x,
                                    tmp2->object->y,head->object->x,head->object->y);
                                // std::cout << ang << ", " << d << std::endl;
                                head->object->x += -d*cos(ang);
                                head->object->y += -d*sin(ang);

                                // head->object->vx *= 0;
                                // head->object->vy *= 0;

                                // head->object->vx *= -dampening2;//* head->object->vx;
                                // head->object->vy *= -dampening2;//* head->object->vy;

                                if(ang == 0 || ang == M_PI){

                                    if(head->object->vy < 0.3){
                                        
                                        head->object->x += pow(-1,1+(rand()%2))*0.01;
                                        head->object->y += pow(-1,1+(rand()%2))*0.01;

                                    }
                                
                                }


                            }
                        
                        }

                    }
                    head = head->prev;
                }
                head = tmp2;
                /////////////////////////////

            }
            head = head->prev;
        }
        head = tmp;

}

void Physics::gravity(List* head,double t){
    
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

float Physics::SmoothingKernel(float radius, float dist){
    // float val = (0, radius-dist);
    std::cout << std::max(0,10) << std::endl;

}