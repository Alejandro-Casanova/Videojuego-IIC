#include "Proyectil.h"
#include "freeglut.h"


Proyectil::Proyectil(void)
{
}

Proyectil::~Proyectil(void) 
{
}


void Proyectil::dibuja(){
	glColor3f(0.0f, 1.0f, 1.0f);
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




float Proyectil::GetPosX(Vector2D vector){
	float x;
	x = vector.x;
	return x;
}

float Proyectil::GetPosY(Vector2D vector){
	float y;
	y = vector.y;
	return y;
}


//																							 SETS DE DIFERENTES VALORES

void Proyectil::setOrigen(float ox, float oy) {
	_origen.x = ox;
	_origen.y = oy;
}

//void Proyectil::setPos(float x, float y){
//	_posicion.x = x;
//	_posicion.y = y;
//}
//
//void Proyectil::setVel(float vx, float vy) {
//	_velocidad.x = vx;
//	_velocidad.y = vy;
//}
//
//void Proyectil::setAcel(float ax, float ay) {
//	_aceleracion.x = ax;
//	_aceleracion.y = ay;
//}

void Proyectil::inicializa()
{
	_radio = 5.0f;
	_origen.set(0, 0);
	_posicion = _origen;
	_velocidad.set(0, 0);
	_aceleracion.set(0, 0);
}





//
//void Proyectil::mueve(float t){
//	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
//	velocidad = velocidad + aceleracion * t;
//}




