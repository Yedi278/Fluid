#include "Vector2.h"
#include "math.h"
// #define M_PI 3.141592

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

float Vector2::get_angle(float x1, float y1, float x2, float y2) {
    // Calcola le differenze nelle coordinate
    //GIRO ANTIORARIO DA DESTRA
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;

    float angoloRad = atan2(deltaY, deltaX);

    float angoloGradi = angoloRad * (180.0 / M_PI);

    if (angoloGradi < 0) {
        angoloGradi += 360.0;
    }

    return angoloGradi;
}

void Vector2::scale(int alpha) {

	this->module *= alpha;

}