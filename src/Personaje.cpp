#include "Personaje.h"
#include <iostream>

Personaje::Personaje(){

}

Personaje::~Personaje(){

}

bool Personaje::dispara()
{
	if (_shootCounter == _shootSpeed) {
		_shootCounter = 0;
		return true;
	}
	return false;
}

void Personaje::dibuja()
{
	//glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	_color.ponColor();
    glutSolidSphere(_radio, 20, 20);
	//glPopMatrix();
	glTranslatef(-_posicion.x, -_posicion.y, 0);
}

void Personaje::inicializa()
{
	setColor(122,40,80);
	setRadio(5);
	setPos(40,0);
}

void Personaje::mueve(float t)
{
	Entidad::mueve(t);
	if (_shootCounter < _shootSpeed) _shootCounter += t;
	else _shootCounter = _shootSpeed;
}
