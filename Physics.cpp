#include <iostream>
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
    // Calcola le differenze nelle coordinate
    //GIRO ANTIORARIO DA DESTRA
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;

    double angoloRad = atan2(deltaY, deltaX);

    double angoloGradi = angoloRad * (180.0 / M_PI);

    if (angoloGradi < 0) {
        angoloGradi += 360.0;
    }
    if(deltaX < 0){
        return angoloRad + M_PI/2;
    }
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

void Physics::gravity(double t){
    
    // SDL_Log("%f",t);
    for(int i=0; i< objArr->size; i++){

        if(objArr->array[i].obj != nullptr){

            objArr->array[i].obj->vy += GRAVITY*t;
            objArr->array[i].obj->y += objArr->array[i].obj->vy*t;

        }
    }
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
                objArr->array[i].obj->vy *= -1 * DAMPENING;
            }
            else if(objArr->array[i].obj->y < y_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->y = y_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vy *= -1 * DAMPENING;
            }

            if(objArr->array[i].obj->x > x_bound_down- objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_down  - objArr->array[i].obj->radius;
                objArr->array[i].obj->vx *= -1 * DAMPENING;
            }
            else if(objArr->array[i].obj->x < x_bound_top+ objArr->array[i].obj->radius){
                objArr->array[i].obj->x = x_bound_top  + objArr->array[i].obj->radius;
                objArr->array[i].obj->vx *= -1 * DAMPENING;
            }

        }
    }
}

float Physics::Density(Vector2* samplePoint){

    float dens = 0;
    const float mass = 1;
    for(int i=0; i<objArr->size; i++){

        float dist = sqrt(pow((objArr->array[i].obj->x-samplePoint->xf),2) + pow((objArr->array[i].obj->y-samplePoint->yf),2));
        float influence = SmoothingKernel(SmthRadius,dist);
        dens += mass*influence;
    }
    return dens;
}

void Physics::resolveCollisions(double time){

    for(int i=0; i<objArr->size; i++){
        for(int j=0; j<objArr->size; j++){
            if((objArr->array[i].obj != nullptr) & (objArr->array[j].obj != nullptr) & (i != j)){

                float d = distance(objArr->array[i].obj, objArr->array[j].obj);
                float k = objArr->array[i].obj->radius + objArr->array[j].obj->radius;

                if( k - d > 1 ){

                    float ang = calcolaAngolo(objArr->array[i].obj->x,objArr->array[i].obj->y,objArr->array[j].obj->x,objArr->array[j].obj->y);
                    // SDL_Log("%d : %f",i,d);

                    float x = CONST*abs(d-k)*cos(ang + M_PI/2);
                    float y = CONST*abs(d-k)*sin(ang + M_PI/2);

                    // SDL_Log("%f, %f , %f",ang*360/M_PI,x,y);

                    objArr->array[i].obj->x += x;
                    objArr->array[i].obj->y += y;
                    objArr->array[j].obj->x -= x;
                    objArr->array[j].obj->y -= y;

                    objArr->array[i].obj->vx *= DAMP;
                    objArr->array[i].obj->vy *= DAMP;
                    objArr->array[j].obj->vx *= DAMP;
                    objArr->array[j].obj->vy *= DAMP;
                }
            }
        }
    }
}