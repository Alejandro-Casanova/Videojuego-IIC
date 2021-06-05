#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"
#include <Caja.h>
#include "Obstaculo.h"
#include "Enemigo.h"
#include "Interaccion.h"
#include "ListaProyectil.h"
#include "Macros.h"
#include "Puerta.h"



class Entidad;
class Enemigo;
class Objeto;
class Player;

class Room
{
	friend class ListaProyectil;

public:
	Room(float indice, const char* ruta_de_textura, Player* playerPtr);
	virtual ~Room();

	virtual void mueve();
	void disparos(); //Gestiona los disparos de los enemigos
	virtual void dibuja();
	void dibujaHitBox() const;

	void inicializa(const char* ruta_de_layout);
	void cargaLayout(const char* ruta_de_archivo);
	void setRoom(); //Inicializa Obst�culos, Enemigos, etc...

	void addPuerta(Puerta* newPuerta); //A�ade una puerta a la room
	Puerta* puertaActual();//Devuelve la puerta que est� en contacto con el jugador, en caso de no haber ninguna, devuelve nullptr
	void muerte(); //El jugador muere
	virtual void gestionarDisparos(ListaProyectil& listaP); //Colisiones de los proyectiles con diferentes elementos de la room

	void setParedes(float ancho, float alto);
	void setAncho(float ancho) { _ancho = ancho; }
	void setAlto(float alto) { _alto = alto; }
	int getIndice() const { return _indice; }
	bool puertasAbiertas() const { return _puertasAbiertas; }

protected:
	const int _indice; //Identifica la room, para diferenciarla del resto de rooms del piso
	float _ancho = ROOM_WIDTH;
	float _alto = ROOM_HEIGHT;
	bool _puertasAbiertas = true;

	Caja _paredes; //Hit-box de las paredes
	ListaProyectil disparosEnemigos;
	Vector2D origen=(-_ancho / 2.0f, +_alto / 2.0f - 10.0f);

	Player* _playerPtr = nullptr;
	std::vector<std::string> _layout; //Dimensiones de la habitaci�n 7x13
	std::vector<Obstaculo*> _obstaculos;
	std::vector<Enemigo*> _enemigos;
	std::vector<Objeto*> _objetos;
	ETSIDI::Sprite _sprite;
	//Puerta _puerta{nullptr};
	std::vector<Puerta*> _puertas;
	
};

class BossRoom : public Room {
public:
	BossRoom(float indice, const char* ruta_de_textura, Player* playerPtr);
	~BossRoom();

	void dibuja() override;
	void mueve() override;
	virtual void gestionarDisparos(ListaProyectil& listaP) override;

private:
	BossGusano* _gusano = nullptr;
	//bool _bossIsDead = false;

};

