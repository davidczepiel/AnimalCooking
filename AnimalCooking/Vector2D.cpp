#include "Vector2D.h"
#include <math.h>
#include "checkML.h"

//Normaliza el vector
void Vector2D::normalize() {
	double mod = sqrt(pow(x, 2) + pow(y, 2)); //Calcula el modulo
	//Divide cada coordenada del vector por el modulo
	if (mod > 0) {
		x /= mod;
		y /= mod;
	}
}

//Suma de dos vectores
//Devuelve un vector con la suma
Vector2D Vector2D::operator+(const Vector2D& v) const {
	return Vector2D(x + v.getX(), y + v.getY());
}

//Resta de dos vectores
//Devuelve un vector con la resta
Vector2D Vector2D::operator-(const Vector2D& v) const {
	return Vector2D(x - v.getX(), y - v.getY());
}

//Multiplicacion de un vector por un numero
//Devuelve un vector con la multilicacion de cada componente por el numero
Vector2D Vector2D::operator*(double n) const {
	return Vector2D(x * n, y * n);
}

//Multiplicacion de un vector por otro vector
//Devuelve un vector con la multiplicacion vectorial de ambos
double Vector2D::operator*(const Vector2D& v) const {
	return ((x * v.getX()) + (y * v.getX()));
}