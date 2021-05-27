#pragma once
#include "Entidad.h"

class Enemigo : public Entidad
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

