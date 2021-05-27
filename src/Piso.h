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
	void inicializa(Entidad* pptr);

private:
	Entidad* _personaje_ptr;

public:
	Room _room;
};

