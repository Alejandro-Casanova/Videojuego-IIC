#pragma once

#include "Personaje.h"
#include <ETSIDI.h>
#include "Caja.h"

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo(Vector2D posicion, Entidad* playerPtr, const char* ruta_de_textura); //Almacena posicion y un puntero al jugador
	virtual ~Enemigo();

	virtual void dibuja() override;
	void inicializa() override;
	void inicializa(Entidad* playerPtr); //Almacena un puntero al jugador

protected:
	Vector2D _dims{ 13.0f, 13.0f }; //Dimensiones del sprite
	void follow(Entidad* ptr); //Modifica la velocidad del enemigo para seguir a una entidad genérica (a menudo será el jugador)
	Entidad* _playerPtr = nullptr; //Almacena un puntero al jugador para poder seguirlo
	ETSIDI::Sprite _sprite;
};

class Caca : public Enemigo {
public:
	Caca(Vector2D pos, Entidad* const playerPtr);
	virtual ~Caca();

	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
};



class Fatty : public Enemigo {
public:
	Fatty(const Vector2D pos, Entidad* const PlayerPtr);
	virtual ~Fatty();

	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
};