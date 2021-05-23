#pragma once

#include "Room.h"
class Personaje;


class Piso
{
	friend class ListaProyectil;

public:
	Piso();
	void mueve();
	void dibuja();
	void inicializa(Personaje* pptr);

private:
	Personaje* _personaje_ptr;

public:
	Room _room;
};

