#include "Vector2.h"

Vector::Vector(float x, float y) {

	this->x = x;
	this->y = y;
	
}

float Vector::angle(){

    double angoloRad = -atan2(-this->y, this->x);
    // double angoloGrad = angoloRad * 360 / (2*M_PI);

    return angoloRad;
}

void Vector::angle(float a){
	float m = mod();
	this->x = m*cos(a);
	this->y = m*sin(a);
}

float Vector::angleGrad(){

    double angoloRad = -atan2(-this->y, this->x);
    double angoloGrad = angoloRad * 360 / (2*3.14159265);

    return angoloGrad;
}

float Vector::mod(){
	return sqrt(pow(this->x,2) + pow(this->y,2));
}

float Vector::mod(float a){

	const float ang = angle();
	this->x = a*cos(ang);
	this->y = a*sin(ang);
}

Vector Vector::operator+(Vector v){
	return Vector(this->x + v.x, this->y + v.y);
}

Vector Vector::operator-(Vector v){
	return Vector(this->x - v.x, this->y-v.y);
}

Vector Vector::operator*(float a){

	float m = mod();
	const float ang = angle();
	m *= a;

	return Vector(m*cos(ang), m*sin(ang));
}

Vector Vector::operator/(float a){

	float m = mod();
	const float ang = angle();
	m /= a;

	return Vector(m*cos(ang), m*sin(ang));
}

void Vector::operator+=(Vector v){

	this->x += v.x;
	this->y += v.y;
}

void Vector::operator-=(Vector v){

	this->x -= v.x;
	this->y -= v.y;
}

void Vector::operator*=(float v){

	float ang = angle();
	this->x = mod()*v*cos(ang);
	this->y = mod()*v*sin(ang);

}

void Vector::operator=(Vector v){
	this->x = v.x;
	this->y = v.y;
}