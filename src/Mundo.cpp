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

Mundo::Mundo() //: _piso{&jugador}
{
	_disparosPlayer.setFriendly(true);

	//_pisos.resize(2);
	_piso = new Piso(&_jugador, "res/pisos/1.txt");
	
}

Mundo::~Mundo()
{
	//for (auto& i : _pisos) delete i;
	if (_piso != nullptr) delete _piso;
}


void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			x_ojo, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	///LLAMADAS PARA DIBUJAR
	_gui.dibuja();
	
	_jugador.dibuja();

	_piso->dibuja();

	//malapersona.dibuja();

	_disparosPlayer.dibuja();
}

void Mundo::siguientePiso()
{
	delete _piso;
	_contadorPisos++;
	_piso = new Piso(&_jugador, "res/pisos/2.txt");
}

void Mundo::mueve()
{
	//LLAMADAS DE ANIMACION
	_piso->mueve();
	_disparosPlayer.mueve(T_CONST);

	_jugador.mueve(T_CONST);
  
	//Interaccion::rebote(malapersona, _piso._room._paredes);
	/*Proyectil* auxi = disparosPlayer.impacto();
	if (auxi != 0) { disparosPlayer.eliminar(auxi);
	malapersona.setPos(-130, 0);
	}*/
	_piso->roomActual()->gestionarDisparos(_disparosPlayer); //Colisiones de los disparos con el entorno y enemigos
}


void Mundo::tecla() {

	_jugador.tecla();

	if (GestorDeTeclado::isKeyPressed(' ')){
		if (_piso->cambiaRoom()) {
			_disparosPlayer.destruirContenido();
		}
		else if (_piso->roomActual()->tipo() == Room::ROOM_TYPE::BOSS) {
			BossRoom* aux = dynamic_cast<BossRoom*>(_piso->roomActual());
			if (aux->juntoTrampilla()) siguientePiso();
		}
	}
}

void Mundo::teclaEspecial()
{
	Proyectil* aux = _jugador.dispara();
	if (aux != nullptr) _disparosPlayer.agregar(aux);

	_jugador.teclaEspecial();
}

void Mundo::inicializa()
{
	x_ojo=-10.0f;
	y_ojo=0.0f;
	z_ojo=140.0f;
	
	//LLAMADAS DE INICIALIZACION
	_jugador.inicializa();
	//_piso.inicializa(&jugador);
	
}

int Mundo::JuegoAcabado() {
	
	if (jugador.getHealthCounter() > 0)
		return 0;

	else
		return 1;

	
}



