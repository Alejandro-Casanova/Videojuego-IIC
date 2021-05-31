#pragma once

#include "Personaje.h"
#include <ETSIDI.h>
#include "Caja.h"

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo();
	Enemigo(Vector2D posicion, Entidad* playerPtr);
	virtual ~Enemigo();

	virtual void dibuja() override;
	void inicializa() override;
	void inicializa(Entidad* playerPtr); //Almacena un puntero al jugador

protected:
	Vector2D _dims; //Dimensiones del sprite
	void follow(Entidad* ptr); //Modifica la velocidad del enemigo para seguir a una entidad genérica (a menudo será el jugador)
	Entidad* _playerPtr = nullptr; //Almacena un puntero al jugador para poder seguirlo
};

class Caca : public Enemigo {
public:
	Caca();
	Caca(Vector2D pos, Entidad* const playerPtr);
	virtual ~Caca();
	//void inicializa() override;
	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
	ETSIDI::Sprite _spriteCaca{ "res/texturas/caca.png" };
};



class Fatty : public Enemigo {
public:
	Fatty();
	Fatty(const Vector2D pos, Entidad* const PlayerPtr);
	virtual ~Fatty();
	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
	ETSIDI::Sprite _spriteFatty{ "res/texturas/fatty.png" };
};