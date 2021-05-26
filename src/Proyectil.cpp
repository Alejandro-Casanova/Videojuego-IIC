#include "Proyectil.h"
#include "freeglut.h"
#include "iostream"


Proyectil::Proyectil()
{
	_radio = 1.0f;
}

Proyectil::~Proyectil() 
{

}

void Proyectil::dibuja(){
	glTranslatef(_posicion.x, _posicion.y, 0);
	_color.ponColor();
	glutSolidSphere(_radio, 20, 20);
	glTranslatef(-_posicion.x, -_posicion.y, 0);
}

//SETS DE DIFERENTES VALORES

void Proyectil::setOrigen(float ox, float oy) {
	_origen.x = ox;
	_origen.y = oy;
}

void Proyectil::inicializa()
{

}





