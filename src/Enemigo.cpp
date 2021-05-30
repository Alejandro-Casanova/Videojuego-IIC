#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo() {

}

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion) {
	_posicion = posicion;
}


void Enemigo::inicializa()
{

}
void Enemigo::dibuja(){
}





void Enemigo::mueve(float t) {
}

/// FATTY

Fatty::Fatty() {
	//_spriteFatty.setSize(13, 13);
}

Fatty::~Fatty()
{
}

Fatty::Fatty(Vector2D pos):Enemigo(pos) {}

void Fatty::dibuja()
{
	_spriteFatty.setPos(_posicion.x, _posicion.y);
	_spriteFatty.setSize(13, 13);
	_spriteFatty.draw();
}

void Fatty::mueve(float t) {
	Entidad::mueve(t);
	_velocidad = (10, 10);
	_spriteFatty.loop();

}


///////////// caca
Caca::Caca(Vector2D pos) :Enemigo(pos) {}

void Caca::dibuja()
{
	_spriteCaca.setPos(_posicion.x, _posicion.y);
	_spriteCaca.setSize(13, 13);
	_spriteCaca.draw();
}

void Caca::mueve(float t) {
	Entidad::mueve(t);
	_velocidad = (10, 10);
	_spriteCaca.loop();

}

Caca::Caca() {
	//_spriteFatty.setSize(13, 13);
}

Caca::~Caca()
{
}