#include "Mundo.h"
#include "freeglut.h"
#include "Proyectil.h"
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "stdio.h"
#include "iostream"
#include "Personaje.h"

using namespace std;


void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	_piso.dibuja();
	
	personaje.dibuja();

	malapersona.dibuja();

	disparosPlayer.dibuja();
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
	_piso.mueve();
	disparosPlayer.mueve(0.025f);
	personaje.mueve(0.025f);
	malapersona.mueve(0.025f);
	Proyectil* auxc = disparosPlayer.colision(_piso._room._paredes);
	if (auxc != 0) disparosPlayer.eliminar(auxc);
	Interaccion::rebote(malapersona, _piso._room._paredes);
	Proyectil* auxi = disparosPlayer.impacto(malapersona);
	if (auxi != 0) { disparosPlayer.eliminar(auxi);
	malapersona.setPos(-130, 0);
	}
}



void Mundo::tecla_disparo(unsigned char key)			//Creacion de proyectil de disparo del jugador
{
	if (key == 'i' || key == 'j' || key == 'k' || key == 'l') {
		// Creacion de un proyectil
		Proyectil* d = new Proyectil();
		//	proyectil.setOrigen(Vector2D.player)
		Vector2D pos = personaje.getPos();
		d->setPos(pos.x, pos.y);
		disparosPlayer.agregar(d);
		Vector2D proyp = d->getPos();
		cout << "proy x = " << proyp.x << " || proy y = " << proyp.y << endl;
		cout << "pers x = " << pos.x << " || pers y = " << pos.y << endl;
;		switch (key)
		{
		case 'j':
			d->setVel(-20, 0);
			break;
		case 'l':
			d->setVel(20, 0);
			break;
		case 'i':
			d->setVel(0, 20);
			break;
		case 'k':
			d->setVel(0, -20);
			break;
		}
	}
}


void Mundo::tecla(unsigned char key) {

	bool arriba = 0, abajo = 0, derecha = 0, izquierda = 0, parar = 0;

	// cout << "tecladown";

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
		personaje.setVel(0, 30);
		
	}
	else if (abajo)
	{
		personaje.setVel(0, -30);
	}

	else if (izquierda)
	{
		personaje.setVel(-30, 0);
	}

	else if (derecha)
	{
		
		personaje.setVel(30, 0);
	}
	else{
		
		personaje.setVel(0, 0);
		personaje.setAcel(0, 0);

	}

	



}


void Mundo::tecla_up(unsigned char key) {

	// cout<<"TECLA UP";


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
	
	personaje.inicializa();
	malapersona.inicializa();
}

Mundo::Mundo()
{



}


