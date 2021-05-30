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
	void inicializa(Entidad* pptr, Room* rpr);

private:
	Entidad* _personaje_ptr = nullptr;

public:
	Room _room;
};

