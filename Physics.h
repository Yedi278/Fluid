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
    Physics(SDL_Window* window, Grid* grid);
    ~Physics();

    void update(double t);
    void boundariesCollisions();
    void circBounds(Vector center, float radius, float time);
    void resolveCollisions(double time);
    void gravity(double t);

};