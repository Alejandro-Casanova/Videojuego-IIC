#pragma once
#include "Pared.h"
#include "Piso.h"
#include "Proyectil.h"
#include "Player.h"
#include "Interaccion.h"
#include "ListaProyectil.h"
#include "Enemigo.h"
#include "Room.h"
#include "GUI.h"


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

	void siguientePiso(); //Pasa al siguiente piso

private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;

	//int _pisoActual = 0; //Indica el piso activo
	//std::vector<Piso*> _pisos;
	Player _jugador;
	int _contadorPisos = 0;
	Piso* _piso = nullptr;
	GUI _gui{ &_jugador };
	//Enemigo malapersona; //TEMPORAL
	ListaProyectil _disparosPlayer;

	//Room* _roomActual = nullptr;
};
