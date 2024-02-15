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

	double get_angle(int x1, int y1, int x2, int y2);
	void scale(int alpha);
};