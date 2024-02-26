#include "Physics.h"
#include "math.h"

#define GRAVITY 9.81
#define DAMPENING 0.7
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

double distance(GameObject* obj1, GameObject* obj2){

    float d = (obj1->pos - obj2->pos).mod();

    return sqrt( pow(obj1->pos.x-obj2->pos.x, 2) + pow(obj1->pos.y - obj2->pos.y, 2) );

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

            grid->objects[i].obj->vel += (grid->objects[i].obj->acc*(t*t));

            grid->objects[i].obj->pos += (grid->objects[i].obj->vel * t);

            SDL_Log("%f, %f, %f",t, grid->objects[i].obj->vel.y, grid->objects[i].obj->acc.y );
            // grid->objects[i].obj->x += 0.5*grid->objects[i].obj->ax*t*t + grid->objects[i].obj->vx*t;
            // grid->objects[i].obj->vx += grid->objects[i].obj->ax*t;    

            // grid->objects[i].obj->y += 0.5*grid->objects[i].obj->ay*t*t + grid->objects[i].obj->vy*t;
            // grid->objects[i].obj->vy += grid->objects[i].obj->ay*t;    

            // grid->objects[i].obj->vx *= 1-AIR_RESIST;
            // grid->objects[i].obj->vy *= 1-AIR_RESIST;
 
        }
    }
}

void Physics::gravity(double t){
    
    for(int i=0; i<grid->size;i++){
        if(grid->objects[i].obj != nullptr){

            grid->objects[i].obj->acc.y = SDL_STANDARD_GRAVITY;
            // grid->objects[i].obj->ay = GRAVITY; 
            // grid->objects[i].obj->ay = GRAVITY;
            // grid->objects[i].obj->vy += grid->objects[i].obj->ay * t;
            // grid->objects[i].obj->y += grid->objects[i].obj->vy *t;

        }
    }
    
}

void Physics::boundariesCollisions(){

    for(int i=0; i<grid->size; i++){
        if(grid->objects[i].obj != nullptr && grid->objects[i].id != -1){
            
            GameObject* tmp = grid->objects[i].obj;

            if(tmp->pos.y > y_bound_down - tmp->radius){
                tmp->pos.y = y_bound_down  - tmp->radius;
                tmp->vel.y *= -DAMPENING;
            }
            else if(tmp->pos.y < y_bound_top+ tmp->radius){
                tmp->pos.y = y_bound_top  + tmp->radius;
                tmp->vel.y *= -DAMPENING;
            }

            if(tmp->pos.x > x_bound_down- tmp->radius){
                tmp->pos.x = x_bound_down  - tmp->radius;
                // tmp->ax *= -DAMPENING;
                tmp->vel.x *= -DAMPENING;
            }
            else if(tmp->pos.x < x_bound_top+ tmp->radius){
                tmp->pos.x = x_bound_top  + tmp->radius;
                tmp->vel.x *= -DAMPENING;
            }

        }
    }
}

void Physics::resolveCollisions(double time){

    // for(int i=0; i<grid->density; i++){
    //     for(int j=0; j<grid->density; j++){
    //         for(int k=0; k<grid->single_cell_size; k++){

    //             int index_fixed = grid->cells[i][j][k];

    //             for(int l=i-1; l<i+1; l++){
    //                 for(int m=j-1; m<j+1; m++){
    //                     for(int n=0; n<grid->single_cell_size; n++){
                            

    //                         if(l<0 || m<0 || l>grid->single_cell_size 
    //                             || m>grid->single_cell_size || index_fixed == -1) continue;

    //                         int index_changing = grid->cells[l][m][n];
    //                         if(index_changing == -1 || index_changing == index_fixed) continue;

    //                         float d = distance(grid->objects[index_fixed].obj,grid->objects[index_changing].obj);

    //                         const float rSum = grid->objects[index_fixed].obj->radius + grid->objects[index_changing].obj->radius;
    //                         if( rSum - d > 0 ){

    //                             float ang = calcolaAngolo( grid->objects[index_fixed].obj->x, grid->objects[index_fixed].obj->y,
    //                                 grid->objects[index_changing].obj->x, grid->objects[index_changing].obj->y);
                                
    //                             double dx = -CONST*abs(d-rSum)*cos(ang);
    //                             double dy = -CONST*abs(d-rSum)*sin(ang);
                                
    //                             grid->objects[index_fixed].obj->x += dx;
    //                             grid->objects[index_fixed].obj->y += dy;
    //                             grid->objects[index_changing].obj->x -= dx;
    //                             grid->objects[index_changing].obj->y -= dy;
    //                             // SDL_Log("[%d][%d] : Ang:%f, x:%lf y:%lf",index_fixed,index_changing,ang,x,y);

    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
}