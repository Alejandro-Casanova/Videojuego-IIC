#include "Mundo.h"
#include "freeglut.h"
#include "Proyectil.h"
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "stdio.h"
#include "iostream"

using namespace std;


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
	case 'j':
		proyectil1.setVel(-15.0f, 0.0f);
		break;
	case 'l':
		proyectil1.setVel(15.0f, 0.0f);
		break;
	case 'i':
		proyectil1.setVel(0.0f, 15.0f);
		break;
	case 'k':
		proyectil1.setVel(0.0f, -15.0f);
		break;
	}
}


void Mundo::tecla(unsigned char key) {

	bool arriba = 0, abajo = 0, derecha = 0, izquierda = 0, parar = 0;
	cout << "tecladown";

	switch (key) {
	case 'w':
	{
		arriba = 1;
		//(personaje.setVel(0, 20);
		//personaje.setVel(0, 10);
		//personaje.setAcel(0, 10);
		//personaje.mueve(0);
		

		break;
	}
	case 's':
		abajo = 1;
		//personaje.setVel(0, -10);
		//personaje.setAcel(0, -2);
		break;
	case 'd':
		derecha = 1;
		//personaje.setVel(10, 0);
		//personaje.setAcel(2, 0);
		break;
	case 'a':
		izquierda = 1;
		//personaje.setVel(-10, 0);
		//personaje.setAcel(-20, 0);
		break;


	
	}

	if (arriba) 
	{
		//personaje.setVel = personaje.setVel +  personaje.setAcel(0.1, 0.1);
		personaje.setVel(0, 10);
		
	}
	else if (abajo)
	{
	
		personaje.setVel(0, -10);
	}

	else if (izquierda)
	{
		
		personaje.setVel(-10, 0);
	}

	else if (derecha)
	{
		
		personaje.setVel(10, 0);
	}
	else{
		
		personaje.setVel(0, 0);
		personaje.setAcel(0, 0);

	}

	



}


void Mundo::tecla_up(unsigned char key) {

	cout<<"TECLA UP";


	if (key == 'w' || key == 's' || key == 'd' || key == 'a') {
		personaje.setVel(0, 0);
		personaje.setAcel(0, 0);
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


