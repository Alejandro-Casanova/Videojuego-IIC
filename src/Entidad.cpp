#include "Entidad.h"
#include <math.h>

#define PI 3.14159265358979323846

Entidad::Entidad() {

}

Entidad::Entidad(Vector2D pos, float radio) : _posicion(pos), _radio(radio)
{
}

Entidad::~Entidad() {

}

void Entidad::mueve(float t)
{
	_posicion = _posicion + _velocidad * t + _aceleracion * (0.5f * t * t);
	_velocidad = _velocidad + _aceleracion * t;
}

void Entidad::dibujaHitbox() const
{
	//Dibuja hitbox circular
	float x = _posicion.x;
	float y = _posicion.y;
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	x += (float)(_radio * cos(359.0 * PI / 180.0));
	y += (float)(_radio * sin(359.0 * PI / 180.0));
	for (int j = 0; j < 360; j++)
	{
		glVertex2f(x, y);
		x = _posicion.x + (float)(_radio * cos(j * PI / 180.0));
		y = _posicion.y + (float)(_radio * sin(j * PI / 180.0));
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

