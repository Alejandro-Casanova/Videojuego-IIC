#pragma once

#include "Personaje.h"
#include "ETSIDI.h"

class Player : public Personaje
{
public:
	Player();
	virtual ~Player();

	void tecla();
	void teclaEspecial();

	virtual void dibuja() override;
	void inicializa() override;
	virtual void mueve(float) override;

	virtual bool recibeHerida(int daño) override;

	int getLlaves() const { return _llaves; }
	int getDinero() const { return _dinero; }

	void flipPos(bool H, bool V);
private:
	int _llaves = 0;
	int _dinero = 0;
	float _damageTimer = 0; //Controla el umbral de invulnerabilidad del jugador tras recibir daño
	ETSIDI::SpriteSequence _body{ "res/texturas/isaac/body_sequence_full.png", 10, 2 };
	ETSIDI::SpriteSequence _head{ "res/texturas/isaac/head_sequence.png", 8 };
	ETSIDI::SpriteSequence _especial{ "res/texturas/isaac/especial.png", 3 };
};

