#pragma once
#include <math.h>

class Vector
{
private:

public:

	float x = 0;
	float y = 0;

	Vector(float x, float y);

	float angle();
	void angle(float a);
	float angleGrad();
	float mod();
	float mod(float a);

	Vector operator+(Vector v);
	Vector operator-(Vector v);
	Vector operator*(float a);
	Vector operator/(float a);
	void operator+=(Vector v);
	void operator-=(Vector v);
	void operator*=(float a);
	void operator/=(Vector v);
	void operator=(Vector v);

};