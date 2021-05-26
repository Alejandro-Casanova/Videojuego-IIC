#include "Entidad.h"

Entidad::Entidad() {

}

Entidad::~Entidad() {

}

void Entidad::mueve(float t)
{
	_posicion = _posicion + _velocidad * t + _aceleracion * (0.5f * t * t);
	_velocidad = _velocidad + _aceleracion * t;

}

void Entidad::setPos(float x, float y)
{
	_posicion.x = x;
	_posicion.y = y;
}

void Entidad::setVel(float vx, float vy)
{
	_velocidad.x = vx;
	_velocidad.y = vy;
}


void Entidad::setAcel(float ax, float ay)
{
	_aceleracion.x = ax;
	_aceleracion.y = ay;

}

Vector2D Entidad::getPos() {

	return _posicion;
}


void Entidad::inicializa()
{
	//setColor(122, 40, 80);
	//setRadio(20);
	//setPos(0, 0)
}

