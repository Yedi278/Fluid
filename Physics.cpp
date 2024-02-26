#include "Physics.h"
#include "math.h"

#define GRAVITY 800
#define DAMPENING 0.4
#define AIR_RESIST 0
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

            grid->objects[i].obj->vx *= 1-AIR_RESIST;
            grid->objects[i].obj->vy *= 1-AIR_RESIST;

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

    for(int i=0; i<grid->size; i++){
        if(grid->objects[i].obj != nullptr && grid->objects[i].id != -1){

            if(grid->objects[i].obj->y > y_bound_down - grid->objects[i].obj->radius){
                grid->objects[i].obj->y = y_bound_down  - grid->objects[i].obj->radius;
                grid->objects[i].obj->ay *= 0;
                grid->objects[i].obj->vy *= -DAMPENING;
            }
            else if(grid->objects[i].obj->y < y_bound_top+ grid->objects[i].obj->radius){
                grid->objects[i].obj->y = y_bound_top  + grid->objects[i].obj->radius;
                grid->objects[i].obj->vy *= -DAMPENING;
            }

            if(grid->objects[i].obj->x > x_bound_down- grid->objects[i].obj->radius){
                grid->objects[i].obj->x = x_bound_down  - grid->objects[i].obj->radius;
                // grid->objects[i].obj->ax *= -DAMPENING;
                grid->objects[i].obj->vx *= -DAMPENING;
            }
            else if(grid->objects[i].obj->x < x_bound_top+ grid->objects[i].obj->radius){
                grid->objects[i].obj->x = x_bound_top  + grid->objects[i].obj->radius;
                grid->objects[i].obj->vx *= -DAMPENING;
            }

        }
    }
}

void Physics::resolveCollisions(double time){

    for(int i=0; i<grid->density; i++){
        for(int j=0; j<grid->density; j++){
            for(int k=0; k<grid->single_cell_size; k++){

                int index_fixed = grid->cells[i][j][k];

                for(int l=i-1; l<i+1; l++){
                    for(int m=j-1; m<j+1; m++){
                        for(int n=0; n<grid->single_cell_size; n++){
                            

                            if(l<0 || m<0 || l>grid->single_cell_size 
                                || m>grid->single_cell_size || index_fixed == -1) continue;

                            int index_changing = grid->cells[l][m][n];
                            if(index_changing == -1 || index_changing == index_fixed) continue;

                            float d = distance(grid->objects[index_fixed].obj,grid->objects[index_changing].obj);

                            const float rSum = grid->objects[index_fixed].obj->radius + grid->objects[index_changing].obj->radius;

                            if( rSum - d > 0 ){

                                float ang = calcolaAngolo(grid->objects[index_fixed].obj->x,grid->objects[index_fixed].obj->y,
                                    grid->objects[index_changing].obj->x,grid->objects[index_changing].obj->y);
                                
                                double x = -CONST*abs(d-rSum)*cos(ang);
                                double y = -CONST*abs(d-rSum)*sin(ang);
                                
                                grid->objects[index_fixed].obj->x += x;
                                grid->objects[index_fixed].obj->y += y;
                                grid->objects[index_changing].obj->x -= x;
                                grid->objects[index_changing].obj->y -= y;
                                // SDL_Log("[%d][%d] : Ang:%f, x:%lf y:%lf",index_fixed,index_changing,ang,x,y);

                            }
                        }
                    }
                }
            }
        }
    }
}