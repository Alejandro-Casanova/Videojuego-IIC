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

	void siguientePiso(); //Pasa al siguiente piso

private:
	float x_ojo = -10.0f;
	float y_ojo = 0;
	float z_ojo = 140.0f;
	int final_juego = 0;

	Player _jugador;
	int _contadorPisos = 0;
	Piso* _piso = nullptr;
	GUI _gui{ &_jugador };
	ListaProyectil _disparosPlayer;

};
