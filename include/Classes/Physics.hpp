#pragma once
#include "Grid.hpp"
#include "math.h"

class Physics
{
private:


    Grid* grid = nullptr;
    SDL_Window* window = nullptr;

    int height = 400;
    int width = 400;

public:

    float gravity_const = (float)0.98;
    float grav_angle = M_PI/2;
    float air_resistance = 0;
    float dampening = 0;
    float rectdamp = 0.f;

    Physics(SDL_Window* window, Grid* grid);
    ~Physics();

    void Euler_ODE(double dt);
    void Runge_Kutta(double dt);
    void update(double t);
    void circBounds(Vector center, float radius, float time);
    void rectBounds(Vector center, float height, float width, float);
    void resolveCollisions(double time,SDL_Renderer* rnd);
    void gravity(double t);
    float Energy();
};