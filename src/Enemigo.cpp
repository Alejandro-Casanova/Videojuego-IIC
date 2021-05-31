#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo() {

}

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion, Entidad* playerPtr) {
	_posicion = posicion;
	_playerPtr = playerPtr;
	_radio = 5.0f;
}

void Enemigo::inicializa()
{

}

void Enemigo::inicializa(Entidad* playerPtr)
{
	inicializa();
	_playerPtr = playerPtr;
}

void Enemigo::dibuja(){

}

void Enemigo::follow(Entidad* ptr)
{
	Vector2D dir = ptr->getPos() - _posicion;
	_velocidad = dir.unitario() * _speedStat;
}

/// FATTY

Fatty::Fatty() {

}

Fatty::~Fatty(){

}

Fatty::Fatty(Vector2D pos, Entidad* playerPtr) : Enemigo(pos, playerPtr) {

	_spriteFatty.setSize(_dims.x, _dims.y);
	_spriteFatty.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
}

void Fatty::dibuja()
{
	dibujaHitbox();
	_spriteFatty.setPos(_posicion.x, _posicion.y);
	_spriteFatty.draw();
}

void Fatty::mueve(float t) {
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteFatty.loop();

}

///////////// caca
Caca::Caca(Vector2D pos, Entidad* const playerPtr) : Enemigo(pos, playerPtr) 
{
	_spriteCaca.setSize(_dims.x, _dims.y);
	_spriteCaca.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
}

void Caca::dibuja()
{
	dibujaHitbox();
	_spriteCaca.setPos(_posicion.x, _posicion.y);
	_spriteCaca.draw();
}

void Caca::mueve(float t) 
{
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteCaca.loop();
}

Caca::Caca(){

}

Caca::~Caca()
{
}