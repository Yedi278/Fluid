#include "Physics.h"

#define GRAVITY 9.81
#define DAMPENING 1
#define AIR_RESIST 0 //from 0 to 1
#define CONST 0.5

Physics::~Physics()
{
    if(this != nullptr){
        delete this;
    }
}

double calcolaAngolo(double x1, double y1, double x2, double y2){
    
    const double deltaX = x2 - x1;
    const double deltaY = y2 - y1;

    double angoloRad = -atan2(-deltaY, deltaX);
    // double angoloGrad = angoloRad * 360 / (2*M_PI);

    return angoloRad;
}


Physics::Physics(SDL_Window* window, Grid* grid)
{
    this->grid = grid;
    this->window = window;
    SDL_GetWindowSize(window,&this->x_bound_down,&this->y_bound_down);
}

void Physics::update(double t){

    for(auto node : grid->objects){

        if(node.obj == nullptr) continue;
        
        node.obj->vel += node.obj->acc * (0.5*t*t);
        node.obj->pos += node.obj->vel * t;
        node.obj->acc = Vector(0,0);
    }
}

void Physics::gravity(double t){
    for(auto node : grid->objects){
        if(node.obj != nullptr){
            node.obj->acc += Vector(0,SDL_STANDARD_GRAVITY);
        }
    }
}

void Physics::boundariesCollisions(){

    // for(int i=0; i<grid->size; i++){
    //     if(grid->objects[i].obj != nullptr && grid->objects[i].id != -1){
            
    //         GameObject* tmp = grid->objects[i].obj;

    //         if(tmp->pos.y > y_bound_down - tmp->radius){
    //             tmp->pos.y = y_bound_down  - tmp->radius;
    //             tmp->vel.y *= -DAMPENING;
    //         }
    //         else if(tmp->pos.y < y_bound_top+ tmp->radius){
    //             tmp->pos.y = y_bound_top  + tmp->radius;
    //             tmp->vel.y *= -DAMPENING;
    //         }

    //         if(tmp->pos.x > x_bound_down- tmp->radius){
    //             tmp->pos.x = x_bound_down  - tmp->radius;
    //             tmp->vel.x *= -DAMPENING;
    //         }
    //         else if(tmp->pos.x < x_bound_top+ tmp->radius){
    //             tmp->pos.x = x_bound_top  + tmp->radius;
    //             tmp->vel.x *= -DAMPENING;
    //         }

    //     }
    // }
}

void Physics::circBounds(Vector center, float radius, float time){
    
    for(auto node : grid->objects){
        if(node.obj != nullptr){

            const Vector oldpos = node.obj->pos;
            Vector d = node.obj->pos - center;

            if((d.mod()+node.obj->radius) > radius){

                d.mod(radius - node.obj->radius);
                node.obj->pos = center + d;
                node.obj->vel += (node.obj->pos - oldpos)/time;
                node.obj->vel *= DAMPENING;
            }
        }
    }
}

void Physics::resolveCollisions(double time){

    for(int i=0; i<grid->density; i++){
        for(int j=0; j<grid->density; j++){
            for(int k=0; k<grid->single_cell_size; k++){

                int index_fixed = grid->cells[i][j][k];
                if(index_fixed == -1) continue;

                for(int l=i-1; l<i+1; l++){
                    for(int m=j-1; m<j+1; m++){
                        for(int n=0; n<grid->single_cell_size; n++){
                            

                            if(l<0 || m<0 || l>grid->single_cell_size 
                                || m>grid->single_cell_size) continue;

                            int index_changing = grid->cells[l][m][n];

                            if(index_changing == -1 || index_changing == index_fixed) continue;

                            Vector dis = grid->objects[index_changing].obj->pos - grid->objects[index_fixed].obj->pos;

                            const float rSum = grid->objects[index_fixed].obj->radius + grid->objects[index_changing].obj->radius;
                            float dp = abs(rSum - dis.mod());

                            if( rSum - dis.mod() > 0 ){
                                
                                dis.mod(dp*0.5);
                                grid->objects[index_changing].obj->pos += dis;
                                grid->objects[index_fixed].obj->pos -= dis;
                                
                            }
                        }
                    }
                }
            }
        }
    }
}