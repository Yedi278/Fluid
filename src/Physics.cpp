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

    for(auto obj : grid->objects){
        // if(!node.obj) continue;
        if(!obj) continue;

        obj->pos += obj->vel*dt + obj->acc * 0.5  * dt*dt;
        obj->vel += obj->acc*dt;

        obj->acc = Vector(0,0);

    }
}

Vector da_dt(int val,Vector pos, Vector vel, Vector acc, double dt){

    switch (val)
    {
        case 1:
            return vel;

        case 2:
            return acc;
    }
}

void RK4(Vector& pos,Vector& vel,Vector& acc, double dt){

        Vector k1 = da_dt(1, pos, vel, acc, 0);
        Vector k2 = da_dt(1, pos+(k1*dt*0.5f), vel+(k1*dt*0.5f), acc+(k1*dt*0.5f),dt*0.5);
        Vector k3 = da_dt(1, pos+(k2*dt*0.5f), vel+(k2*dt*0.5f), acc+(k2*dt*0.5f),dt*0.5);
        Vector k4 = da_dt(1, pos+(k3*dt), vel+(k3*dt), acc+(k3*dt),dt);
        pos += (k1 + k2*2 + k3*2 + k4) * dt/6 + acc*0.5*dt*dt;

        vel += acc*dt;

        // Vector k11 = da_dt(2, pos, vel, acc, dt);
        // Vector k22 = da_dt(2, pos+(k11*dt*0.5f), vel+(k11*dt*0.5f), acc+(k11*dt*0.5f),dt*0.5);
        // Vector k33 = da_dt(2, pos+(k22*dt*0.5f), vel+(k22*dt*0.5f), acc+(k22*dt*0.5f),dt*0.5);
        // Vector k44 = da_dt(2, pos+(k33*dt), vel+(k33*dt), acc+(k33*dt),dt);
        // vel += (k11 + k22*2 + k33*2 + k44) * dt/6;

}

void Physics::Runge_Kutta(double dt){

    for(auto obj : grid->objects){
        if(!obj) continue;

        RK4(obj->pos,obj->vel,obj->acc,dt);

        obj->acc = Vector(0,0);
    }
}

void Physics::update(double dt){

    // Euler_ODE(dt);
    Runge_Kutta(dt);

}

void Physics::gravity(double dt){

    for(auto obj : grid->objects){
        if(obj){
            obj->acc += Vector(0.f,gravity_const);
            obj->acc.angle(grav_angle);
        }
    }
}

void Physics::rectBounds(Vector center, float h, float w, float dt){

    for(auto obj : grid->objects){
        if(obj){

            Vector dist = obj->pos - center;
            float radius = obj->radius;

            if(dist.x - w/2 + radius > 0){
                dist.x = w/2 - radius;
                obj->pos = center + dist;
                obj->vel.x *= -1;
                obj->vel *= 1-dampening;

            }
            if(dist.x + w/2 - radius < 0){
                dist.x = -w/2 + radius;
                obj->pos = center + dist;
                obj->vel.x *= -1;
                obj->vel *= 1-dampening;

            }

            if(dist.y - h/2 + radius > 0){
                dist.y = h/2 - radius;
                obj->pos = center + dist;
                obj->vel.y *= -1;
                obj->vel *= 1-dampening;

            }
            if(dist.y + h/2 - radius < 0){
                dist.y = -h/2 + radius;
                obj->pos = center + dist;
                obj->vel.y *= -1;
                obj->vel *= 1-dampening;

            }
        }
    }
}

void Physics::circBounds(Vector center, float radius, float time){
    
    for(auto obj : grid->objects){
        if(obj){

            Vector d = obj->pos - center;

            if((d.mod()+obj->radius) > radius){

                d.mod(radius - obj->radius);
                obj->pos = center + d;

                obj->vel.x *= -1;
                obj->vel *= 1-dampening;

            }
        }
    }
}

Vector reflect(Vector n, Vector v){

    Vector other = v;
    other.angle(v.angle() - n.angle() + 3.1415/2.); //trasformazione di coordinate (ruoto a 0)

    other.y *= -1;  //inverto il moto

    float angle = other.angle();
    other.angle(angle + n.angle() - 3.1415/2.);     //ritorno alle coordinate originali

    return other;
}

void collide(GameObject* m1, GameObject* m2){

    Vector dis = m2->pos - m1->pos;
    float Rsum = m1->radius + m2->radius;

    dis.mod((Rsum - dis.mod())*0.5);
    m1->pos -= dis;
    m2->pos += dis;

    m1->vel = reflect(dis,m1->vel);
    m2->vel = reflect(dis,m2->vel);
}

// void Physics::resolveCollisions(double time,SDL_Renderer* rnd){

//     for(int i=0; i<grid->density; i++){
//         for(int j=0; j<grid->density; j++){
//             for(auto index_fixed : grid->cells[i][j]){ if(index_fixed == -1 || !grid->objects[index_fixed].obj) continue;

//                 for(int l=i-1; l<i+1; l++){
//                     for(int m=j-1; m<j+1; m++){ if(l<0 || l>grid->single_cell_size || m<0 || m>grid->single_cell_size) continue;
                        
//                         for(auto index_changing : grid->cells[l][m]){
//                             if(index_changing == -1 || index_changing == index_fixed 
//                                                     || !grid->objects[index_changing].obj) continue;
                            
//                             Vector dis_centers = grid->objects[index_changing].obj->pos - grid->objects[index_fixed].obj->pos;

//                             const float rSum = grid->objects[index_fixed].obj->radius 
//                                              + grid->objects[index_changing].obj->radius;
                            
//                             float dp = rSum - dis_centers.mod();

//                             if( dp > 0 ){
                                
//                                 collide(grid->objects[index_changing].obj,grid->objects[index_fixed].obj);

//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

float Physics::Energy(){

    float energy = 0;

    for(auto obj : grid->objects){
        if(obj){

            float kin = 0.5 * obj->m * obj->vel.mod()*obj->vel.mod();
            float pot = obj->m * gravity_const * obj->pos.y;
            energy += abs(kin - pot);
        }
    }
    return energy;
}

void Physics::resolveCollisions(double time,SDL_Renderer* rnd){
    for(auto obj : grid->objects){ if(obj){

            for(auto obj2 : grid->objects){ if(obj2){ if(obj == obj2) continue;

                    Vector dis = obj2->pos - obj->pos;

                    float Rs = obj->radius + obj2->radius;

                    if(Rs - dis.mod() > 0){
 
                        collide(obj,obj2);

                    }
                }
            }
        }
    }
}
