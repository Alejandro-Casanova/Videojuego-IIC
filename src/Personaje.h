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
	virtual void dibuja() override = 0; //Personaje es una clase abstracta
	void inicializa() override;
	virtual void mueve(float) override;

	Vector2D getHealth () const { return Vector2D{ _healthCounter, _healthStat }; }

protected:
	float _healthStat = 0.0f; //Salud Máxima
	float _healthCounter = 0.0f; //Contador de salud
	float _speedStat = 10.0f; //Velocidad de desplazamiento
	float _shootSpeed = 1.0f; //Segundos entre disparos
	float _shootCounter = 0.0f; //Contador para controlar la frecuencia de disparo
	float _meleeDamage = 1.0f;
	float _shotDamage = 1.0f;
};

