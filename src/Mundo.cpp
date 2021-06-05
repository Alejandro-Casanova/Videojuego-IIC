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

	jugador.tecla();

	if (GestorDeTeclado::isKeyPressed(' ')){
		if (_piso.cambiaRoom()) {
			disparosPlayer.destruirContenido();
		}
	}
}

void Mundo::teclaEspecial()
{
	Proyectil* aux = jugador.dispara();
	if (aux != nullptr) disparosPlayer.agregar(aux);

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




