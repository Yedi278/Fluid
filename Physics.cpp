#include "Physics.h"
#include "math.h"

#define GRAVITY 800
#define DAMPENING 0
#define DAMP 0.9
#define SmthRadius 100
#define CONST 0.5

int signum(float x){
	if(x<0) return -1;
	if(x>0) return 1;
}

double calcolaAngolo(double x1, double y1, double x2, double y2) {
    
    const double deltaX = x2 - x1;
    const double deltaY = y2 - y1;

    double angoloRad = -atan2(-deltaY, deltaX);
    double angoloGrad = angoloRad * 360 / (2*M_PI);
    
    // if(deltaX < 0 & deltaY > 0){
    //     return M_PI - angoloRad;
    // }
    // if(deltaX < 0 & deltaY < 0){
    //     return M_PI + angoloRad;
    // }

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

Physics::Physics(ObjectArray* objArr,SDL_Window* window)
{
    this->objArr = objArr;
    this->window = window;
    SDL_GetWindowSize(window,&this->x_bound_down,&this->y_bound_down);
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

void Physics::update(double t){

    for(int i=0; i<objArr->size; i++){
        if(objArr->array[i].obj != nullptr){

            objArr->array[i].obj->vx += objArr->array[i].obj->ax*t;    
            objArr->array[i].obj->x += 0.5*objArr->array[i].obj->ax*t*t + objArr->array[i].obj->vx*t;

            objArr->array[i].obj->vy += objArr->array[i].obj->ay*t;    
            objArr->array[i].obj->y += 0.5*objArr->array[i].obj->ay*t*t + objArr->array[i].obj->vy*t;
        
        }

    }
}

void Physics::gravity(double t){
    
    for(int i=0; i< objArr->size; i++){

        if(objArr->array[i].obj != nullptr){

            // objArr->array[i].obj->vy += GRAVITY*t;
            // objArr->array[i].obj->y += objArr->array[i].obj->vy*t;
            objArr->array[i].obj->ay = GRAVITY;

        }
    }
}

void Physics::boundariesCollisions(){

    for(int i=0; i<objArr->size; i++){
        if(objArr->array[i].obj != nullptr){

            if(objArr->array[i].obj->y > y_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_down  - objArr->array[i].obj->radius;
                // objArr->array[i].obj->ay *= -DAMPENING;
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
                float k = objArr->array[i].obj->radius + objArr->array[j].obj->radius;

                if( k - d > 0 ){

                    float ang = calcolaAngolo(objArr->array[i].obj->x,objArr->array[i].obj->y,objArr->array[j].obj->x,objArr->array[j].obj->y);
                    
                    double x = -CONST*abs(d-k)*cos(ang);
                    double y = -CONST*abs(d-k)*sin(ang);

                    // SDL_Log("i:%d a:%f x:%lf y:%lf , abd:%f",i, atan2(-10,0), x,y, d);

                    objArr->array[i].obj->x += x;
                    objArr->array[i].obj->y += y;
                    objArr->array[j].obj->x -= x;
                    objArr->array[j].obj->y -= y;

                    // objArr->array[i].obj->vx *= DAMP;
                    // objArr->array[i].obj->vy *= DAMP;
                    // objArr->array[j].obj->vx *= DAMP;
                    // objArr->array[j].obj->vy *= DAMP;
                }
            }
        }
    }
}