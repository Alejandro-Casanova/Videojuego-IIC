#include "Mundo.h"
#include "freeglut.h"
#include "Proyectil.h"
#include <math.h>

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	_piso.dibuja();
	proyectil1.dibuja();
	personaje.dibuja();
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
	_piso.mueve();
	proyectil1.mueve(0.025f);
	personaje.mueve(0.025f);
}



void Mundo::tecla_disparo(unsigned char key)			//Creacion de proyectil de disparo del jugador
{
	// Creacion de un proyectil
	//	proyectil.setOrigen(Vector2D.player)

	switch (key)
	{
	case GLUT_KEY_LEFT:
		proyectil1.setVel(-5.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		proyectil1.setVel(5.0f, 0.0f);
		break;
	case GLUT_KEY_UP:
		proyectil1.setVel(0.0f, 5.0f);
		break;
	case GLUT_KEY_DOWN:
		proyectil1.setVel(0.0f, -5.0f);
		break;
	}
}


void Mundo::tecla(unsigned char key){
	switch (key) {
	case 'w':
		personaje.setVel(0, 5);
		break;
	case 's':
		personaje.setVel(0, -5);
		break;
	case 'd':
		personaje.setVel(5,0);
		break;
	case 'a':
		personaje.setVel(-5, 0);
		break;
	}
}


void Mundo::inicializa()
{
	x_ojo=0.0f;
	y_ojo=0.0f;
	z_ojo=120.0f;

	//LLAMADAS DE INICIALIZACION
	_piso.inicializa(&personaje);

	//Proyectil proyectil1;
	proyectil1.inicializa();
	personaje.inicializa();
}

Mundo::Mundo()
{
}


