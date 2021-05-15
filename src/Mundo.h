#pragma once
#include "Pared.h"
#include "Piso.h"
#include "Proyectil.h"
#include"Personaje.h"
#include "Interaccion.h"
#include "ListaProyectil.h"


class Mundo{
Proyectil proyectil1;
Personaje personaje;
ListaProyectil disparosPlayer;
//ListaProyectil disparosEnemigo;



public: 
	Mundo();
	void tecla(unsigned char key);
	void tecla_up(unsigned char key);
	void tecla_disparo(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();

private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;

	Piso _piso;
	
};
