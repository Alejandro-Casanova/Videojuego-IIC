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

Mundo::Mundo()
{

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
	disparosPlayer.mueve(0.025f);

	jugador.mueve(0.025f);
  
	//malapersona.mueve(0.025f);
  
	
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

			if (GestorDeTeclado::isKeyDown('j'))
				d->setVel(-20, 0);
			else if (GestorDeTeclado::isKeyDown('l'))
				d->setVel(20, 0);
			else if (GestorDeTeclado::isKeyDown('i'))
				d->setVel(0, 20);
			else if (GestorDeTeclado::isKeyDown('k'))
				d->setVel(0, -20);

		}
	}
	jugador.tecla();
	if (GestorDeTeclado::isKeyPressed(' ')){
		_piso.cambiaRoom();
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
	//malapersona.inicializa();
	_piso.inicializa(&jugador);
	

	
}




