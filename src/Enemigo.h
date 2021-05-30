#pragma once

#include "Personaje.h"
#include <ETSIDI.h>
#include "Caja.h"

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo();
	Enemigo(Vector2D posicion);
	//Enemigo(const char* ruta_de_textura, Caja hitBox);
	//Enemigo(Caja hitBox);
	virtual ~Enemigo();

	//void cargaTextura(const char* ruta_de_textura);
	//void setHitBox(Vector2D vert1, Vector2D vert2) { _hitBox.setParedes(vert1, vert2); } //V�rtices opuestos de la caja
	//void setBordeTextura(float bordeTextura) { _bordeTextura = bordeTextura; }

	virtual void dibuja() override;
	void inicializa() override;
	void mueve(float t);


	//Caja _hitBox;
	Vector2D _posicion;
	//bool _playerFlag = true, _bulletFlag = true; //Define si se realiza colisi�n con jugador o proyectil
	//double _ancho = 10, _alto = 10; //Dimensiones predeterminadas
	//float _bordeTextura = 0.0f; //Por si la hit-box es menor que la textura
	//ETSIDI::GLTexture _textura = { 0, 0, 0 };
	ETSIDI::Sprite _sprite{"res/texturas/caca.png"};

private:

};
