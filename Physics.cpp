#include <iostream>
#include <algorithm>

#include "Physics.h"
#include "math.h"

#define GRAVITY 0.0002
#define dampening 0.2
#define dampening2 0.3


Physics::Physics(ObjectArray* objArr)
{
    this->objArr = objArr;
}

Physics::Physics(ObjectArray* objArr,int x_top, int x_down, int y_top, int y_down)
{
    this->objArr = objArr;
    this->x_bound_top = x_top;
    this->x_bound_down = x_down;
    this->y_bound_top = y_top;
    this->y_bound_down = y_down;

}

Physics::~Physics()
{
    if(this != nullptr){
        delete this;
    }
}


double distance(GameObject* obj1, GameObject* obj2){

    return sqrt(pow((obj1->x-obj2->x),2) + pow((obj1->y-obj2->y),2));
}


void Physics::gravity(double t){
    
    for(int i=0; i< objArr->size; i++){

        if(objArr->array[i].obj != nullptr){

            objArr->array[i].obj->vy += GRAVITY*t;
            objArr->array[i].obj->y += objArr->array[i].obj->vy*t;

        }
    }
}

float max(float x, float y){
    if(x > y) return x;
    else return y;
    return y;
}

float Physics::SmoothingKernel(float radius, float dist){

    // SDL_Log("%f",max(0,radius-dist));
    return pow(max(0,radius-dist),3);
}

void Physics::boundariesCollisions(){

    for(int i=0; i<objArr->size; i++){
        if(objArr->array[i].obj != nullptr){

            if(objArr->array[i].obj->y > y_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_down  - objArr->array[i].obj->radius;
                objArr->array[i].obj->vy *= -1 * dampening;
            }
            else if(objArr->array[i].obj->y < y_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vy *= -1 * dampening;
            }

            if(objArr->array[i].obj->x > x_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_down  - objArr->array[i].obj->radius;
                objArr->array[i].obj->vx *= -1 * dampening;
            }
            else if(objArr->array[i].obj->x < x_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vx *= -1 * dampening;
            }

        }
    }
}

void Physics::resolveCollisions(){
}
