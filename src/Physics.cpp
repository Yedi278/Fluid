#include "Physics.h"

Physics::~Physics()
{
    delete this;
}

Physics::Physics(SDL_Window* window, Grid* grid)
{
    this->grid = grid;
    this->window = window;
    SDL_GetWindowSize(window,&this->x_bound_down,&this->y_bound_down);
}

void Physics::update(double dt){

    for(auto node : grid->objects){

        if(node.obj == nullptr) continue;
        
        node.obj->vel += node.obj->acc * dt;
        node.obj->pos += node.obj->vel * dt;
        node.obj->acc = Vector(0,0);

    }
}

void Physics::gravity(double t){

    for(auto node : grid->objects){
        if(node.obj != nullptr){
            node.obj->acc += Vector(0.f,gravity_const);
        }
    }
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
                node.obj->vel *= 1-dampening;

            }
        }
    }
}

void Physics::resolveCollisions(double time,SDL_Renderer* rnd){

    for(int i=0; i<grid->density; i++){
        for(int j=0; j<grid->density; j++){
            for(auto index_fixed : grid->cells[i][j]){
                if(index_fixed == -1) continue;

                for(int l=i-1; l<i+1; l++){
                    for(int m=j-1; m<j+1; m++){
                        if(l<0 || m<0 || l>grid->single_cell_size 
                               || m>grid->single_cell_size) continue;
                        
                        for(auto index_changing : grid->cells[l][m]){
                            if(index_changing == -1 || index_changing == index_fixed) continue;
                            
                            Vector dis_centers = grid->objects[index_changing].obj->pos - grid->objects[index_fixed].obj->pos;

                            const float rSum = grid->objects[index_fixed].obj->radius 
                                             + grid->objects[index_changing].obj->radius;
                            
                            float dp = rSum - dis_centers.mod();

                            if( dp > 0 ){
                                
                                // dis_centers *= 0.5;
                                dis_centers.mod(dp*0.5);
                                grid->objects[index_changing].obj->pos -= dis_centers;
                                grid->objects[index_fixed].obj->pos += dis_centers;

                                SDL_Log("%f, %f",grid->objects[index_changing].obj->vel.mod(),grid->objects[index_fixed].obj->vel.mod());
                                
                            }
                        }
                    }
                }
            }
        }
    }
}

float Physics::Energy(){

    float energy = 0;

    for(auto node : grid->objects){
        if(node.obj != nullptr){

            energy += 0.5* node.obj->m * pow(node.obj->vel.mod(),2);
            energy += node.obj->m * gravity_const * node.obj->pos.y;

        }
    }
    return energy;
}