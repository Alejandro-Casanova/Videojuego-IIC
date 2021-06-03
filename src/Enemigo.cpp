#include "Enemigo.h"
#include <iostream>

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion, Entidad* playerPtr, const char* ruta_de_textura) : _sprite{ ruta_de_textura } {
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

Fatty::~Fatty(){

}

Fatty::Fatty(Vector2D pos, Entidad* playerPtr) : Enemigo(pos, playerPtr, "res/texturas/fatty.png") {

	_sprite.setSize(_dims.x, _dims.y);
	_sprite.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
}

void Fatty::dibuja()
{
	dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

void Fatty::mueve(float t) {
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteFatty.loop();

}

///////////// caca
Caca::Caca(Vector2D pos, Entidad* const playerPtr) : Enemigo(pos, playerPtr, "res/texturas/caca.png")
{
	_sprite.setSize(_dims.x, _dims.y);
	_sprite.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
}

void Caca::dibuja()
{
	dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

void Caca::mueve(float t) 
{
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteCaca.loop();
}

Caca::~Caca()
{
}