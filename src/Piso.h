#pragma once

#include "Room.h"
class Personaje;

class Piso
{
public:
	Piso();
	void mueve();
	void dibuja();
	void inicializa(Personaje* pptr);

private:
	Room _room;
	Personaje* _personaje_ptr;
};

