#pragma once
#include <iostream>

class Vector2D {
private:
	double x = 0;
	double y = 0;
public:
	Vector2D() : x(0), y(0) {}
	Vector2D(double x, double y) : x(x), y(y) {}
	double getX() const { return x; }
	double getY() const { return y; }
	void setX(double newX) { x = newX; }
	void setY(double newY) { y = newY; }
	void normalize();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& d) const;
};

using Point2D = Vector2D;