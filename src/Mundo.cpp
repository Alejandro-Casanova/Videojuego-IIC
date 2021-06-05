#include "Mundo.h"
#include "freeglut.h"
#include "Proyectil.h"
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "stdio.h"
#include "iostream"
#include "Personaje.h"
#include "GestorDeTeclado.h"

using namespace std;

Mundo::Mundo() : _piso{&jugador}
{
	disparosPlayer.setFriendly(true);
}

Mundo::~Mundo()
{
}


void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			x_ojo, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	_gui.dibuja();
	
	jugador.dibuja();

	_piso.dibuja();

	//malapersona.dibuja();

	disparosPlayer.dibuja();
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
	_piso.mueve();
	disparosPlayer.mueve(T_CONST);

	jugador.mueve(T_CONST);
  
	//Interaccion::rebote(malapersona, _piso._room._paredes);
	/*Proyectil* auxi = disparosPlayer.impacto();
	if (auxi != 0) { disparosPlayer.eliminar(auxi);
	malapersona.setPos(-130, 0);
	}*/
	_piso.getRoomActual()->gestionarDisparos(disparosPlayer); //Colisiones de los disparos con el entorno y enemigos
}


void Mundo::tecla() {
	//DISPARO
	if (GestorDeTeclado::isKeyDown('j') || GestorDeTeclado::isKeyDown('k') || GestorDeTeclado::isKeyDown('l') || GestorDeTeclado::isKeyDown('i')) {
		if (jugador.dispara()) { //Indica si el jugador está listo para disparar
			// Creacion de un proyectil
			Proyectil* d = new Proyectil();
			//	proyectil.setOrigen(Vector2D.player)
			Vector2D pos = jugador.getPos();
			d->setPos(pos.x, pos.y);
			disparosPlayer.agregar(d);
			Vector2D proyp = d->getPos();

			float vel = jugador.getBulletSpeed();
			if (GestorDeTeclado::isKeyDown('j'))
				d->setVel(-vel, 0);
			else if (GestorDeTeclado::isKeyDown('l'))
				d->setVel(vel, 0);
			else if (GestorDeTeclado::isKeyDown('i'))
				d->setVel(0, vel);
			else if (GestorDeTeclado::isKeyDown('k'))
				d->setVel(0, -vel);

		}
	}
	jugador.tecla();
	if (GestorDeTeclado::isKeyPressed(' ')){
		if (_piso.cambiaRoom()) {
			disparosPlayer.destruirContenido();
		}
	}
}

void Mundo::teclaEspecial()
{
	
	jugador.teclaEspecial();
}

void Mundo::inicializa()
{
	x_ojo=-10.0f;
	y_ojo=0.0f;
	z_ojo=140.0f;
	
	//LLAMADAS DE INICIALIZACION
	jugador.inicializa();
	_piso.inicializa(&jugador);
	

	
}




