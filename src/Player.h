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

	void flipPos(bool H, bool V);
private:
	ETSIDI::SpriteSequence _body{ "res/texturas/body_sequence_full.png", 10, 2 };
	ETSIDI::SpriteSequence _head{ "res/texturas/head_sequence.png", 8 };
};

