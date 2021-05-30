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
	void inicializa(Player* pptr);

private:
	Entidad* _personaje_ptr = nullptr;

public:
	Room _room;
};

