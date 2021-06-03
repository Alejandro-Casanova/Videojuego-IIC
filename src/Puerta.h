#pragma once
#include <ETSIDI.h>
#include <Caja.h>
class Room;

class Puerta
{
public:
	enum class TIPO{LEFT = 0, RIGHT, UP, DOWN};
	Puerta(Room* room, TIPO t = TIPO::UP);
	void dibuja();
	void open() { _sprite.setState(1); }
	void close() { _sprite.setState(0); }

	Room* getNextRoom() { return _roomPtr; }
	const Caja& getHitBox() { return _hitBox; }
	TIPO getTipo() { return _tipo; }
private:
	ETSIDI::SpriteSequence _sprite{ "res/texturas/puerta.png", 2 };
	Caja _hitBox;
	Vector2D _posicion;
	Room* _roomPtr = nullptr;
	TIPO _tipo;
};

