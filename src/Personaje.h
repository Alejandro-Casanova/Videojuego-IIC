#pragma once

#include "Vector2D.h"
#include "freeglut.h"
#include "Entidad.h"

class Personaje : public Entidad
{
public:
	Personaje();
	virtual ~Personaje();

	bool dispara();
	virtual void dibuja() override;
	void inicializa() override;
	virtual void mueve(float) override;

protected:
	float _healthStat = 0.0f;
	float _speedStat = 10.0f;
	float _shootSpeed = 1.0f;
	float _shootCounter = 0.0f; 
};

