#pragma once

#include "Caja.h"
#include <ETSIDI.h>

class Vector2D;

class Obstaculo
{
	friend class Interaccion;
public:
	Obstaculo();
	Obstaculo(Vector2D posicion, const char* ruta_de_textura);
	Obstaculo(const char* ruta_de_textura, Caja hitBox);
	Obstaculo(Caja hitBox);

	void dibuja() const;

	void cargaTextura(const char* ruta_de_textura);
	void setHitBox(Vector2D vert1, Vector2D vert2){ _hitBox.setParedes(vert1, vert2); } //Vértices opuestos de la caja
	void setBordeTextura(float bordeTextura) { _bordeTextura = bordeTextura; }

	Caja _hitBox;
	Vector2D _posicion;
	bool _playerFlag = true, _bulletFlag = true; //Define si se realiza colisión con jugador o proyectil
	double _ancho = 10, _alto = 10; //Dimensiones predeterminadas
	float _bordeTextura = 0.0f; //Por si la hit-box es menor que la textura
	ETSIDI::GLTexture _textura = { 0, 0, 0 };
	ETSIDI::Sprite _sprite(const char);
	
private:
	
};

