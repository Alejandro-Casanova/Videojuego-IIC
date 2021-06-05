#pragma once
#include <ETSIDI.h>
#include <Caja.h>
#include "Macros.h"


class Room;
class Piso;

class Puerta {
public:
	Puerta(Vector2D posicion = Vector2D(0.0f, 0.0f));
	virtual void open() {  _isOpen = true; }
	virtual void close() { _isOpen = false; }
	const Caja& getHitBox() { return _hitBox; }
	bool isOpen() const { return _isOpen; }
protected:
	Caja _hitBox;
	Vector2D _posicion;
	bool _isOpen = false;
	
};

class PuertaRoom : public Puerta
{
public:
	enum class ORIENTACION{LEFT = 0, RIGHT, UP, DOWN};
	PuertaRoom(Room* room, ORIENTACION t = ORIENTACION::UP, const char* ruta = "res/texturas/puerta.png", int pxW = 49, int pxH = 33, float maxDim = TILE_WIDTH * 1.5f, float offset = 0.0f); //Se carga esta textura por defecto
	virtual ~PuertaRoom();

	void dibuja();
	void open() override { _sprite.setState(1); _isOpen = true; }
	void close() override { _sprite.setState(0); _isOpen = false; }

	Room* getNextRoom() { return _roomPtr; }
	ORIENTACION getOrientacion() { return _orientacion; }
	
protected:
	ETSIDI::SpriteSequence _sprite;
	Room* _roomPtr = nullptr;
	ORIENTACION _orientacion;
	
};

class PuertaBoss : public PuertaRoom {
public:
	PuertaBoss(Room* room, ORIENTACION t);
};

class Trampilla : public Puerta{ //Realmente no hereda de la clase puerta, es muy diferente
public:
	Trampilla(Vector2D pos, const char* ruta_de_sprite = "res/texturas/trapdoor.png", int pxW = 96, int pxH = 96, float maxDim = TILE_WIDTH);
	void dibuja();

private:
	ETSIDI::Sprite _sprite;
	Piso* _pisoPtr = nullptr;

};