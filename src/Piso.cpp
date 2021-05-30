#include "Piso.h"
#include <iostream>
#include <Personaje.h>

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

void Piso::inicializa(Entidad* pptr)
{
	_room.inicializa("res/rooms/test.txt", "res/texturas/Basement1.png", pptr);
	_personaje_ptr = pptr;
	//Prueba
	std::cout << std::endl;
}
