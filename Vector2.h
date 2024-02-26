#pragma once
#include <math.h>

class Vector
{
private:

public:

	float x = 0;
	float y = 0;

	Vector(int x, int y);

	float angle();
	float angleGrad();
	float mod();

	Vector operator+(Vector v);
	Vector operator-(Vector v);
	Vector operator*(float a);
	Vector operator/(float a);
	Vector operator+=(Vector v);
	Vector operator-=(Vector v);
	Vector operator*=(float a);
	Vector operator/=(Vector v);



	float distance(Vector v);
};