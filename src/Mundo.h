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
public: 
	Mundo();
	virtual ~Mundo();

	void tecla();
	void teclaEspecial();
	void inicializa();
	void mueve();
	void dibuja();

	void siguientePiso(); //Pasa al siguiente piso

	int JuegoAcabado(); //devuelve un 0 si no se ha acabado, un 1 si se ha perdido y un 2 si se ha ganado
	int getContadorPisos() const { return _contadorPisos; }
	const Player& getPlayer() const { return _jugador; }

private:
	float x_ojo = -10.0f;
	float y_ojo = 0;
	float z_ojo = 140.0f;

	Player _jugador;
	int _contadorPisos = 0;
	Piso* _piso = nullptr;
	GUI _gui{ &_jugador };
	ListaProyectil _disparosPlayer;

};
