#include "Physics.h"
#include "math.h"

#define GRAVITY 800
#define DAMPENING 0
#define DAMP 0.9
#define SmthRadius 100
#define CONST 0.5


Physics::~Physics()
{
    if(this != nullptr){
        delete this;
    }
}

double calcolaAngolo(double x1, double y1, double x2, double y2) {
    
    const double deltaX = x2 - x1;
    const double deltaY = y2 - y1;

    double angoloRad = -atan2(-deltaY, deltaX);
    // double angoloGrad = angoloRad * 360 / (2*M_PI);

    return angoloRad;
}

double distance(GameObject* obj1, GameObject* obj2){

    return sqrt(pow((obj1->x - obj2->x),2) + pow((obj1->y - obj2->y),2));
}

float max(float x, float y){
    if(x > y) return x;
    else return y;
    return y;
}

Physics::Physics(SDL_Window* window, Grid* grid)
{
    this->grid = grid;
    this->window = window;
    SDL_GetWindowSize(window,&this->x_bound_down,&this->y_bound_down);
}

void Physics::update(double t){

    for(int i=0; i<grid->size;i++){
        if(grid->objects[i].obj != nullptr){

            grid->objects[i].obj->vx += grid->objects[i].obj->ax*t;    
            grid->objects[i].obj->x += 0.5*grid->objects[i].obj->ax*t*t + grid->objects[i].obj->vx*t;

            grid->objects[i].obj->vy += grid->objects[i].obj->ay*t;    
            grid->objects[i].obj->y += 0.5*grid->objects[i].obj->ay*t*t + grid->objects[i].obj->vy*t;
        
        }
    }
}

void Physics::gravity(double t){
    
    for(int i=0; i<grid->size;i++){
        if(grid->objects[i].obj != nullptr){

            grid->objects[i].obj->ay = GRAVITY;
        }
    }
    
}

void Physics::boundariesCollisions(){

    for(int i=0; i<objArr->size; i++){
        if(objArr->array[i].obj != nullptr){

            if(objArr->array[i].obj->y > y_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_down  - objArr->array[i].obj->radius;
                objArr->array[i].obj->ay -= GRAVITY;
                objArr->array[i].obj->vy *= -DAMPENING;
            }
            else if(objArr->array[i].obj->y < y_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vy *= -DAMPENING;
            }

            if(objArr->array[i].obj->x > x_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_down  - objArr->array[i].obj->radius;
                // objArr->array[i].obj->ax *= -DAMPENING;
                objArr->array[i].obj->vx *= -DAMPENING;
            }
            else if(objArr->array[i].obj->x < x_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vx *= -DAMPENING;
            }
            


        }
    }
}

void Physics::resolveCollisions(double time){

    for(int i=0; i<objArr->size; i++){
        for(int j=0; j<objArr->size; j++){
            if((objArr->array[i].obj != nullptr) & (objArr->array[j].obj != nullptr) & (i != j)){

                float d = distance(objArr->array[i].obj, objArr->array[j].obj);
                const float k = objArr->array[i].obj->radius + objArr->array[j].obj->radius;

                if( k - d > 0 ){

                    float ang = calcolaAngolo(objArr->array[i].obj->x,objArr->array[i].obj->y,objArr->array[j].obj->x,objArr->array[j].obj->y);
                    
                    double x = -CONST*abs(d-k)*cos(ang);
                    double y = -CONST*abs(d-k)*sin(ang);
                    
                    objArr->array[i].obj->x += x;
                    objArr->array[i].obj->y += y;
                    objArr->array[j].obj->x -= x;
                    objArr->array[j].obj->y -= y;
                }
            }
        }
    }
}