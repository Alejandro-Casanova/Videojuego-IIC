#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo() {

}

Enemigo::~Enemigo() {

}

void Enemigo::dibuja()
{
	//glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	_color.ponColor();
	glutSolidSphere(_radio, 20, 20);
	//glPopMatrix();
	glTranslatef(-_posicion.x, -_posicion.y, 0);
}

void Enemigo::inicializa()
{
	setColor(240, 60, 80);
	setRadio(5);
	
	_posicion.x = rand() % 70 - 35;
	_posicion.y = rand() % 40 - 20;

	setPos(0, 0);// _posicion.x, _posicion.y);
}


void Enemigo::mueve(float t) {
	Entidad::mueve(t);
	_velocidad = (10, 10);

}