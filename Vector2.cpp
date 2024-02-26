#include "Vector2.h"

Vector::Vector(int x, int y) {

	this->x = x;
	this->y = y;
	
}

float Vector::angle(){

    double angoloRad = -atan2(-this->y, this->x);
    // double angoloGrad = angoloRad * 360 / (2*M_PI);

    return angoloRad;
}

float Vector::angleGrad(){

    double angoloRad = -atan2(-this->y, this->x);
    double angoloGrad = angoloRad * 360 / (2*M_PI);

    return angoloGrad;
}

float Vector::mod(){
	return sqrt(pow(this->x,2) + pow(this->y,2));
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

Vector Vector::operator+=(Vector v){

	this->x += v.x;
	this->y += v.y;
}

Vector Vector::operator-=(Vector v){

	this->x -= v.x;
	this->y -= v.y;
}

Vector Vector::operator*=(float v){

	this->x = mod()*v*cos(angle());
	this->y = mod()*v*sin(angle());
}