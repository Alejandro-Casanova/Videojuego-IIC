#pragma once

#include "Macros.h"
#include "Caja.h"
#include <ETSIDI.h>

class Vector2D;

class Obstaculo
{
	friend class Interaccion;
public:
	Obstaculo(Vector2D posicion, const char* ruta_de_textura);

	void dibuja();

	void setHitBox(Vector2D vert1, Vector2D vert2){ _hitBox.setParedes(vert1, vert2); } //Vértices opuestos de la caja
	void setBordeTextura(float bordeTextura) { _bordeTextura = bordeTextura; }
	const Caja& getHitBox() const { return _hitBox; }

protected:
	Caja _hitBox;
	Vector2D _posicion;
	bool _playerFlag = true, _bulletFlag = true; //Define si se realiza colisión con jugador o proyectil
	double _ancho = TILE_WIDTH, _alto = TILE_WIDTH; //Dimensiones predeterminadas
	float _bordeTextura = 0.0f; //Por si la hit-box es menor que la textura
	ETSIDI::Sprite _sprite;
};


class Roca : public Obstaculo {
public:
	Roca(Vector2D posicion);
	
	ETSIDI::Sprite _sprite{ "res/texturas/rocas.png" };
private:

};

class Hueco : public Obstaculo {
public:
	Hueco(Vector2D posicion);
	ETSIDI::Sprite _sprite{ "res/texturas/hole.png" };
private:

};

