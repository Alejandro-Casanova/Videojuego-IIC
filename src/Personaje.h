#pragma once

#include "Vector2D.h"
#include "freeglut.h"
#include "Entidad.h"

class Personaje : public Entidad
{
	friend class Interaccion;
public:
	Personaje();
	virtual ~Personaje();

	virtual void dibuja() override;
	void inicializa() override;

private:

};

