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
	glTranslatef(posicion.x, posicion.y, 0);
	glutSolidSphere(radio, 20, 20);
	glTranslatef(-posicion.x, -posicion.y, 0);
	glBegin(GL_LINES);
	glVertex3f(posicion.x, posicion.y, 0);
	glVertex3f(origen.x, origen.y, 0);
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
	origen.x = ox;
	origen.y = oy;
}

void Proyectil::setPos(float x, float y){
	posicion.x = x;
	posicion.y = y;
}

void Proyectil::setVel(float vx, float vy) {
	velocidad.x = vx;
	velocidad.y = vy;
}

void Proyectil::setAcel(float ax, float ay) {
	aceleracion.x = ax;
	aceleracion.y = ay;
}

void Proyectil::inicializa(void)
{
	radio = 5;
	origen.setPos(0, 0);
	posicion = origen;
	velocidad.setPos(0, 0);
	aceleracion.setPos(0, 0);
}






void Proyectil::mueve(float t){
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}




