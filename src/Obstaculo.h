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

private:
	Caja _hitBox;
	bool _playerFlag = true, _bulletFlag = true; //Define si se realiza colisión con jugador o proyectil
	float _ancho = 10, _alto = 10; //Dimensiones predeterminadas
	float _bordeTextura = 0.0f; //Por si la hit-box es menor que la textura
	ETSIDI::GLTexture _textura = { 0, 0, 0 };
};

