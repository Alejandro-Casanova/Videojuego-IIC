#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D(float nx, float ny) : x(nx), y(ny)
{
}

Vector2D::~Vector2D() {
}

float Vector2D::modulo() {
	return (float)sqrtf(x * x + y * y);
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

Vector2D Vector2D::operator - (Vector2D v) const
{
	Vector2D res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
Vector2D Vector2D::operator + (Vector2D v) const
{
	Vector2D res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

float Vector2D::operator * (Vector2D v) const{
	return v.x * x + v.y * y;
}

Vector2D Vector2D::operator * (float escalar) const{
	Vector2D resultado;
	resultado.x = escalar * x;
	resultado.y = escalar * y;
	return resultado;
}

Vector2D Vector2D::operator+(float escalar) const
{

	return Vector2D(x + escalar, y + escalar);
}

Vector2D Vector2D::operator+=(Vector2D v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D Vector2D::operator-=(Vector2D v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D Vector2D::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

void Vector2D::setXY(float nx, float ny)
{
	x = nx;
	y = ny;
}

void Vector2D::set(double modulo, double angulo) {
	x = modulo * cos(angulo * 2.0 * PI / 360.0);
	y = modulo * sin(angulo * 2.0 * PI / 360.0);
}