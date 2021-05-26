#include "Personaje.h"
#include <iostream>

Personaje::Personaje(){

}

Personaje::~Personaje(){

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
	setPos(0,0);
}
