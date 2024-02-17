#include "ObjectList.h"

class Physics
{
private:


    ObjectArray* objArr = nullptr;
    SDL_Window* window = nullptr;

    int x_bound_top = 0;
    int x_bound_down = 400;

    int y_bound_top = 0;
    int y_bound_down = 400;

public:
    Physics(ObjectArray* objArr,SDL_Window* window);
    Physics(ObjectArray* objArr,int x_top, int x_down, int y_top, int y_down);
    ~Physics();

    void update(double t);
    void boundariesCollisions();
    void resolveCollisions(double time);
    void gravity(double t);

};