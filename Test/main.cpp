#include <iostream>
#include <math.h>
#define PI 3.141592

int sign(float a){
	if(a > 0) return 1;
	if(a < 0) return -1;
	return 0;
}

float angle(float x, float y){
    
	// if(y == 0 && x < 0) return -PI;
	// if(x == 0) return (float)sign(y)*PI/2;
	// if(x > 0) return atan2(y,x);
	// if(x < 0) return atan2(y,x) + (float)sign(y) * PI;
    return atan2(y,x);
}

int main(int argc, const char* argv[]){



    printf("%f\n", angle(0,-1)*360/(2*3.14159265));

    return 0;
}