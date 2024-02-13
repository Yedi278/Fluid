#include "ObjectList.h"

class Physics
{
private:
    int x_bound_top = 0;
    int x_bound_down = 600;

    int y_bound_top = 0;
    int y_bound_down = 600;
    ObjectArray* objArr = nullptr;

public:
    Physics(ObjectArray* objArr);
    Physics(ObjectArray* objArr,int x_top, int x_down, int y_top, int y_down);
    ~Physics();

    void boundariesCollisions();
    void resolveCollisions();
    void gravity(double t);
    float SmoothingKernel(float radius, float dist);
};