#include "Piso.h"

Piso::Piso() : _room("res/rooms/test.txt")
{

}

void Piso::mueve()
{
	_room.mueve();
}

void Piso::dibuja()
{
	_room.dibuja();
}

void Piso::inicializa()
{
	_room.inicializa();
}
