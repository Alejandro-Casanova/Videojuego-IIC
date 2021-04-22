#include "Mundo.h"
#include "freeglut.h"
#include <math.h>

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	pared_izq.dibuja();
	pared_sup.dibuja();
	pared_der.dibuja();
	pared_inf.dibuja();
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
}

void Mundo::inicializa()
{
	x_ojo=0.0f;
	y_ojo=0.0f;
	z_ojo=30.0f;

	//LLAMADAS DE INICIALIZACION
	pared_izq.setLimites(-10.0f, -10.0f, -10.0f, 10.0f);
	pared_sup.setLimites(-10.0f, 10.0f, 10.0f, 10.0f);
	pared_der.setLimites(10.0f, 10.0f, 10.0f, -10.0f);
	pared_inf.setLimites(-10.0f, -10.0f, 10.0f, -10.0f);
}

void Mundo::tecla(unsigned char key)
{

}
