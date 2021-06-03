#pragma once

#include "Room.h"
class Personaje;


class Piso
{
public:
	Piso();
	void mueve();
	void dibuja();

	bool cambiaRoom(); //Cambia de room si el jugador usa las puertas

	void inicializa(Player* pptr); //Inicialia con un puntero al jugador y una referencia a un puntero a la room actual
	void cargaLayout(const char* ruta_de_archivo); //Carga el layout del piso desde un .txt
	void setPiso(); //Configura las distintas rooms y puertas que conectan las mismas

	Room* getRoomActual() { return _rooms[_roomActual]; }
	void setRoomActual(int nRoom) { if(nRoom != -1) _roomActual = nRoom; }

private:
	int _roomActual = 0;
	Player* _playerPtr = nullptr;
	std::vector<Room*> _rooms; //Vector que contiene únicamente las rooms, será el de uso habitual

	//Vectores auxiliares, su uso es únicamente para la inicialización
	std::vector<std::vector<Room*>> _roomLayout; //Mapa 2D con los punteros a las rooms, útil para inicializar las puertas
	std::vector<std::string> _layout; //Mapa 2D con el layout, identico al documento de texto, util para inicializar las rooms
	
};

