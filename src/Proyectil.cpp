#include "Proyectil.h"
#include "freeglut.h"
#include "iostream"


Proyectil::Proyectil(void)
{
	_radio = 1;
	//_origen.set(0, 0);
	//_posicion = _origen;
	//_velocidad.setVel(0, 20);
	//_aceleracion.set(0, 0);
}

Proyectil::~Proyectil(void) 
{

}


void Proyectil::dibuja(){

	
	glColor3f(_color.r, _color.g, _color.b);
	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glutSolidSphere(_radio, 20, 20);
	glTranslatef(-_posicion.x, -_posicion.y, 0);
	glBegin(GL_LINES);
	glVertex3f(_posicion.x, _posicion.y, 0);
	glVertex3f(_origen.x, _origen.y, 0);
	glEnd();
	glPopMatrix();
}




//				 SETS DE DIFERENTES VALORES

void Proyectil::setOrigen(float ox, float oy) {
	_origen.x = ox;
	_origen.y = oy;
}



void Proyectil::inicializa()
{
	
	//setColor(255, 0, 255);
	//setRadio(1.5);
	//setPos(0, 0);
	//setVel(0, 20);
	
}

//void Proyectil::setPos1(float ix, float iy)
//{
//	Entidad::setPos(ix, iy);
//
//	_origen = _posicion;
//
//}




//void Proyectil::mueve(float t){
//	_posicion = _posicion + _velocidad * t + _aceleracion * (0.5f * t * t);
//	_velocidad = _velocidad + _aceleracion * t;
//}




