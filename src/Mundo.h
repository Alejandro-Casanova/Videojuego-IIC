#pragma once
#include "Pared.h"
#include "Piso.h"
#include "Proyectil.h"
//#include"Personaje.h"
#include "Player.h"
#include "Interaccion.h"
#include "ListaProyectil.h"
#include "Enemigo.h"


class Mundo{
friend class ListaProyectil;

public: 
	Mundo();
	//void tecla(unsigned char key);
	void tecla();
	void teclaEspecial();
	//void tecla_up(unsigned char key);
	//void tecla_disparo(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();

private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;

public:
	Piso _piso;
	Player jugador;
	Enemigo malapersona; //TEMPORAL
	ListaProyectil disparosPlayer; //TEMPORAL?? Tal vez tener una lista proyectil por room, tal vez reiniciarla al cambiar de room
};
