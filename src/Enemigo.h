#pragma once

#include "Personaje.h"

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo();
	virtual ~Enemigo();

	virtual void dibuja() override;
	void inicializa() override;
	void mueve(float t);

private:

};

