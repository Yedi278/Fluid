#include <math.h>

class Vector2
{
private:

public:
	float x=0;
	float y=0;
	int xf = 0;
	int yf = 0;
	double module = 1;
	double angle = 0;

	Vector2(int xf, int yf);
	Vector2(int x, int y, double mod, double angle);
	Vector2(int x, int y, int xf, int yf);

	// Vector2* operator+(Vector2& vect);

	void update(int x, int y, double mod, double angle);
	void update(int x, int y, int xf, int yf);

	float get_angle(float x1, float y1, float x2, float y2);
	void scale(int alpha);
};