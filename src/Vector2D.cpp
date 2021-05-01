#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D(float nx, float ny) : x(nx), y(ny)
{
}

Vector2D::~Vector2D() {
}

float Vector2D::modulo() {
	return (float)sqrt(x * x + y * y);
}

float Vector2D::argumento() {
	return (float)atan2(y, x);
}

Vector2D Vector2D::unitario()
{
	Vector2D retorno(x, y);
	float mod = modulo();
	if (mod > 0.00001)
	{
		retorno.x /= mod;
		retorno.y /= mod;
	}
	return retorno;
}

Vector2D Vector2D::operator - (Vector2D v)
{
	Vector2D res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
Vector2D Vector2D::operator + (Vector2D v)
{
	Vector2D res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

float Vector2D::operator * (Vector2D v) {
	return v.x * x + v.y * y;
}

Vector2D Vector2D::operator * (float escalar) {
	Vector2D resultado;
	resultado.x = escalar * x;
	resultado.y = escalar * y;
	return resultado;
}

void Vector2D::setPos(float x, float y)
{
	x = x;
	y = y;
}
