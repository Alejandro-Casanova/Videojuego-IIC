#pragma once

#include "Room.h"
class Personaje;


class Piso
{
public:
	Piso();
	void mueve();
	void dibuja();
	void inicializa(Entidad* pptr, Room* &rpr);

private:
	Entidad* _personaje_ptr = nullptr;
	Room _room;
};

