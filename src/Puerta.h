#pragma once
#include <ETSIDI.h>
#include <Caja.h>
#include "Macros.h"
class Room;

class Puerta
{
public:
	enum class TIPO{LEFT = 0, RIGHT, UP, DOWN};
	Puerta(Room* room, TIPO t = TIPO::UP, const char* ruta = "res/texturas/puerta.png", int pxW = 49, int pxH = 33, float maxDim = TILE_WIDTH * 1.5f, float offset = 0.0f); //Se carga esta textura por defecto
	virtual ~Puerta();
	void dibuja();
	void open() { _sprite.setState(1); _isOpen = true; }
	void close() { _sprite.setState(0); _isOpen = false; }

	Room* getNextRoom() { return _roomPtr; }
	const Caja& getHitBox() { return _hitBox; }
	TIPO getTipo() { return _tipo; }
	bool isOpen() const { return _isOpen; }
private:
	ETSIDI::SpriteSequence _sprite;
	Caja _hitBox;
	Vector2D _posicion;
	Room* _roomPtr = nullptr;
	TIPO _tipo;
	bool _isOpen = false;
};

class PuertaBoss : public Puerta {
public:
	PuertaBoss(Room* room, TIPO t);

};
