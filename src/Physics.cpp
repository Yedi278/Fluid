#include "Physics.hpp"

Physics::~Physics()
{
    delete this;
}

Physics::Physics(SDL_Window* window, Grid* grid)
{
    this->grid = grid;
    this->window = window;
    SDL_GetWindowSize(window,&this->height,&this->width);
}

void Physics::Euler_ODE(double dt){

    for(auto node : grid->objects){
        if(!node.obj) continue;
        
        Vector oldpos = node.obj->pos;

        node.obj->vel += node.obj->acc*dt;
        node.obj->pos += node.obj->vel*dt + node.obj->acc * 0.5  * dt*dt;

        node.obj->acc = Vector(0,0);

    }
}

void Physics::Runge_Kutta(double dt){



    for(auto node : grid->objects){
        if(!node.obj) continue;
        
        

    }

}


void Physics::update(double dt){

    Euler_ODE(dt);

}

void Physics::gravity(double t){

    for(auto node : grid->objects){
        if(node.obj){
            node.obj->acc += Vector(0.f,gravity_const);
            node.obj->acc.angle(grav_angle);
        }
    }
}

void Physics::rectBounds(Vector center, float h, float w, float dt){

    for(auto node : grid->objects){
        if(node.obj){

            Vector dist = node.obj->pos - center;
            float radius = node.obj->radius;

            if(dist.x - w/2 + radius > 0){
                dist.x = w/2 - radius;
                node.obj->pos = center + dist;
                node.obj->vel.x *= -1;
                node.obj->vel *= 1-dampening;

            }
            if(dist.x + w/2 - radius < 0){
                dist.x = -w/2 + radius;
                node.obj->pos = center + dist;
                node.obj->vel.x *= -1;
                node.obj->vel *= 1-dampening;

            }

            if(dist.y - h/2 + radius > 0){
                dist.y = h/2 - radius;
                node.obj->pos = center + dist;
                node.obj->vel.y *= -1;
                node.obj->vel *= 1-dampening;

            }
            if(dist.y + h/2 - radius < 0){
                dist.y = -h/2 + radius;
                node.obj->pos = center + dist;
                node.obj->vel.y *= -1;
                node.obj->vel *= 1-dampening;

            }
        }
    }
}

void Physics::circBounds(Vector center, float radius, float time){
    
    for(auto node : grid->objects){
        if(node.obj){

            // const Vector oldpos = node.obj->pos;
            Vector d = node.obj->pos - center;

            if((d.mod()+node.obj->radius) > radius){

                d.mod(radius - node.obj->radius);
                node.obj->pos = center + d;

                // node.obj->vel += (node.obj->pos - oldpos)/time;
                node.obj->vel.x *= -1;
                node.obj->vel *= 1-dampening;

            }
        }
    }
}

void Physics::resolveCollisions(double time,SDL_Renderer* rnd){

    for(int i=0; i<grid->density; i++){
        for(int j=0; j<grid->density; j++){
            for(auto index_fixed : grid->cells[i][j]){
                if(index_fixed == -1 || !grid->objects[index_fixed].obj) continue;

                for(int l=i-1; l<i+1; l++){
                    for(int m=j-1; m<j+1; m++){
                        if(l<0 || l>grid->single_cell_size 
                            || m<0 || m>grid->single_cell_size) continue;
                        
                        for(auto index_changing : grid->cells[l][m]){
                            if(index_changing == -1 || index_changing == index_fixed 
                                                    || !grid->objects[index_changing].obj) continue;
                            
                            Vector dis_centers = grid->objects[index_changing].obj->pos - grid->objects[index_fixed].obj->pos;

                            const float rSum = grid->objects[index_fixed].obj->radius 
                                             + grid->objects[index_changing].obj->radius;
                            
                            float dp = rSum - dis_centers.mod();

                            grid->objects[index_fixed].obj->other = Vector(0,0);

                            if( dp > 0 ){
                                
                                dis_centers.mod(dp*0.5f);
                                float angle = dis_centers.angle();
                                dis_centers.angle(angle+3.1415);
                                grid->objects[index_fixed].obj->other = dis_centers;
                                grid->objects[index_changing].obj->pos += dis_centers;
                                // // grid->objects[index_changing].obj->vel += dis_centers*time*0.98;

                                // grid->objects[index_fixed].obj->pos += dis_centers;
                                // grid->objects[index_fixed].obj->vel -= dis_centers*time*0.98;

                                // grid->objects[index_changing].obj->vel *= 0.99;
                                // grid->objects[index_fixed].obj->vel *= 0.99;

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
        if(node.obj){

            float kin = 0.5 * node.obj->m * node.obj->vel.mod()*node.obj->vel.mod();
            float pot = node.obj->m * gravity_const * node.obj->pos.y;
            SDL_Log("%f, %f", kin, pot);
            energy += kin - pot;
        }
    }
    return energy;
}
