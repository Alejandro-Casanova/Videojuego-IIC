#include "Personaje.h"

Personaje::Personaje(){

}

Personaje::~Personaje(){

}

void Personaje::dibuja()
{
	//glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3ub(_r,_g,_b);
    glutSolidSphere(_radio, 20, 20);
	//glPopMatrix();
}

void Personaje::mueve(float t)
{
	_posicion = _posicion + _velocidad * t + _aceleracion * (0.5f * t * t);
	_velocidad = _velocidad + _aceleracion * t;

}

void Personaje :: setPos(float x, float y)
{ 
  _posicion.x = x; 
  _posicion.y = y; 
}

void Personaje::setVel(float vx, float vy)
{
	_velocidad.x = vx;
	_velocidad.y = vy;
}
void Personaje::inicializa()
{
	setColor(122,40,80);
	setRadio(10);
	setPos(0,0);

}
