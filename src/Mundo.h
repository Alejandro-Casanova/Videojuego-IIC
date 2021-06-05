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
	int JuegoAcabado(); //devuelve un 0 si no se ha acabado, un 1 si se ha perdido y un 2 si se ha ganado

	


private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;
	int final_juego = 0;

	Piso _piso;
	std::vector<Piso*> _pisos;
	Player jugador;
	GUI _gui{ &jugador };
	//Enemigo malapersona; //TEMPORAL
	ListaProyectil disparosPlayer;

	//Room* _roomActual = nullptr;
};
