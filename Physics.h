#include "ObjectList.h"

class Physics
{
private:
    int x_bound_top = 0;
    int x_bound_down = 500;

    int y_bound_top = 0;
    int y_bound_down = 500;

    List* head = nullptr;

public:
    Physics(List* head);
    Physics(int x_top, int x_down, int y_top, int y_down);
    ~Physics();

    void boundariesCollisions();
    void resolveCollisions(List* head);
    void gravity(List* head,double t);
};