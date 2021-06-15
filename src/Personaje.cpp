#include "Personaje.h"
#include <iostream>
#include <ETSIDI.h>

Personaje::Personaje(){

}

Personaje::Personaje(Vector2D pos, float radio) : Entidad(pos, radio)
{
}

Personaje::~Personaje(){

}

bool Personaje::puedeDisparar()
{
	if (_shootCounter == _shootSpeed) { //Si el contador está lleno
		_shootCounter = 0;
		return true;
	}
	return false;
}

bool Personaje::recibeHerida(float daño)
{
	_healthCounter -= daño;
	if (_healthCounter <= 0) {
		sonidoMuerte();
		return true;
	}
	return false;
}

void Personaje::sonidoMuerte()
{
	ETSIDI::play("res/audio/monster_death.wav");
}

void Personaje::inicializa()
{
	setColor(122,40,80);
	setRadio(5.0f);
	setPos(0.0f, 0.0f);
}

void Personaje::mueve(float t)
{
	Entidad::mueve(t);
	//Actualiza el contador de disparos
	if (_shootCounter < _shootSpeed) _shootCounter += t; //Aumenta el contador
	else _shootCounter = _shootSpeed; //Si se sobrepasa el umbral
}
