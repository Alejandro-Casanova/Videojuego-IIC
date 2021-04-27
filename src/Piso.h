#pragma once

#include "Room.h"

class Piso
{
public:
	Piso();
	void mueve();
	void dibuja();
	void inicializa();

private:
	Room _room;
};

