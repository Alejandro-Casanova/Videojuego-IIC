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
	int JuegoAcabado(); //devuelve un 0 si no se ha acabado, un 1 si se ha ganado y un 2 si se ha perdido
	int Getfinal_juego() { return final_juego; } //0=juego sigue, 1=victoria, 2=derrota,


private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;
	int final_juego;

	Piso _piso;
	Player jugador;
	Enemigo malapersona; //TEMPORAL
	ListaProyectil disparosPlayer;
	//Room* _roomActual = nullptr;
};
