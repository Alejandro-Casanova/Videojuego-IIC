#pragma once
#include "Pared.h"
#include "Piso.h"
#include "Proyectil.h"
#include "Player.h"
#include "Interaccion.h"
#include "ListaProyectil.h"
#include "Enemigo.h"
#include "Room.h"


class Mundo{
friend class ListaProyectil;

public: 
	Mundo();
	virtual ~Mundo();

	void tecla();
	void teclaEspecial();
	void inicializa();
	void mueve();
	void dibuja();

private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;

	Piso _piso;
	Player jugador;
	Enemigo malapersona; //TEMPORAL
	ListaProyectil disparosPlayer;

	//Room* _roomActual = nullptr;
};
