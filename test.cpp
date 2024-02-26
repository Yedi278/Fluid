#include "Vector2.h"
#include <iostream>
using namespace std;


int main(){
    
    Vector v1 = Vector(10,30);

    Vector v2 = Vector(20,20);

    v2 *= 2;

    printf("x: %f,y: %f, ang: %f, mod: %f\n",v2.x, v2.y, v2.angleGrad(), v2.mod());
    
}