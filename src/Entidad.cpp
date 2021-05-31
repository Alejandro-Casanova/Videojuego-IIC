#include "Entidad.h"
#include <math.h>

#define PI 3.14159265358979323846

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

void Entidad::dibujaHitbox() const
{
	float x = _posicion.x;
	float y = _posicion.y;
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	x += (float)_radio * cos(359 * PI / 180.0f);
	y += (float)_radio * sin(359 * PI / 180.0f);
	for (int j = 0; j < 360; j++)
	{
		glVertex2f(x, y);
		x = _posicion.x + (float)_radio * cos(j * PI / 180.0f);
		y = _posicion.y + (float)_radio * sin(j * PI / 180.0f);
		glVertex2f(x, y);
	}
	glEnd();
}


void Entidad::inicializa()
{
	//setColor(122, 40, 80);
	//setRadio(20);
	//setPos(0, 0)
}

