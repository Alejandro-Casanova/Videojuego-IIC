#include "Piso.h"

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
}
