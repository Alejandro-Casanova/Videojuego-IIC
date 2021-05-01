#include "Mundo.h"
#include "freeglut.h"
#include <math.h>

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	piso.dibuja();
	personaje.dibuja();
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
	piso.mueve();
	personaje.mueve(0.025f);
}

void Mundo::inicializa()
{
	x_ojo=0.0f;
	y_ojo=0.0f;
	z_ojo=120.0f;

	//LLAMADAS DE INICIALIZACION
	piso.inicializa();
	personaje.inicializa();
}

Mundo::Mundo()
{
}

void Mundo::tecla(unsigned char key)
{
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
