#pragma once
#include "Grid.h"
#include "math.h"

class Physics
{
private:


    Grid* grid = nullptr;
    SDL_Window* window = nullptr;

    int x_bound_top = 0;
    int x_bound_down = 400;

    int y_bound_top = 0;
    int y_bound_down = 400;

public:

    float gravity_const = (float)SDL_STANDARD_GRAVITY;
    float air_resistance = 0;
    float dampening = 0;
    
    Physics(SDL_Window* window, Grid* grid);
    ~Physics();

    void update(double t);
    void circBounds(Vector center, float radius, float time);
    void resolveCollisions(double time,SDL_Renderer* rnd);
    void gravity(double t);
    float Energy();
};