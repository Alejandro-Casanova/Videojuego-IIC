#include "Piso.h"
#include <iostream>

Piso::Piso()
{

}

void Piso::mueve()
{
	_room.mueve();
}

void Piso::dibuja()
{
	_room.dibujaHitBox();
	_room.dibuja();

	
	
}

void Piso::inicializa()
{
	_room.inicializa("res/rooms/test.txt", "res/texturas/Basement1.png");

	//Prueba
	std::cout << std::endl;
	_room.setObstaculos();
}
