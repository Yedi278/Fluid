#include "Vector2.h"
#include "math.h"
// # define M_PI	3.14159265358979323846  /* pi */



Vector2::Vector2(int xf, int yf) {
	this->x = 0;
	this->y = 0;
	this->module = sqrt((xf*xf) + (yf*yf));
	this->angle = get_angle(0,0,xf,yf);
	this->xf = xf;
	this->yf = yf;
}

Vector2::Vector2(int x, int y, double mod, double angle) {
	this->x = x;
	this->y = y;
	this->module = mod;
	this->angle = angle;
	this->xf = x+mod * sin(angle);
	this->yf = y+mod * cos(angle);
}

Vector2::Vector2(int x, int y, int xf, int yf) {

	this->x = x;
	this->y = y;
	this->xf = xf;
	this->yf = yf;

	this->module = sqrt((x - xf) * (x - xf) + (y - yf) * (y - yf));
	this->angle = get_angle(x, y, xf, yf);
}

Vector2 Vector2::operator+(Vector2 const& vect) {

	Vector2* tmp = new Vector2(0,0);
	tmp->x = this->x + vect.x;
	tmp->y = this->y + vect.y;
	tmp->xf = this->xf + vect.xf;
	tmp->yf = this->yf + vect.yf;

	return *tmp;
}

void Vector2::update(int x, int y, double mod, double angle) {
	this->x = x;
	this->y = y;
	this->module = mod;
	this->angle = angle;
	this->xf = x+mod * sin(angle);
	this->yf = y+mod * cos(angle);
}

void Vector2::update(int x, int y, int xf, int yf) {
	this->x = x;
	this->y = y;
	this->xf = xf;
	this->yf = yf;

	this->module = sqrt((x - xf) * (x - xf) + (y - yf) * (y - yf));
	this->angle = get_angle(x, y, xf, yf);
}

double Vector2::get_angle(int x1, int y1, int x2, int y2) {

	if (x2>x1) {
		return atan((y2 - y1) / (x2 - x1));
	}
	else if (x2<x1) {
		return -atan((y2 - y1) / (x2 - x1));
	}
	else if (x2 == x1) {
		return M_PI;
	}
	return 0;
}

void Vector2::scale(int alpha) {

	this->module *= alpha;

}